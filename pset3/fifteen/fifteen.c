/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// track the empty space
// array contains two vals
// first tracks i, second j
int empty_space[2];

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void print_empty(void);
// new
void get_tile_position(int tile_position[], int tile);
bool handle_switch_tiles(int idx, int tile_position[], int tile);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();
        printf("\n");
        print_empty();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    int total_tiles = (d * d) - 1;
    // with an odd # total, we need to swap 1 and 2
    bool should_swap = total_tiles % 2 != 0;
    // apply dimensions to board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (total_tiles <= 2 && total_tiles > 0 && should_swap)
            {

                if (total_tiles == 2)
                {
                    board[i][j] = 1;
                }
                else
                {
                    board[i][j] = 2;
                }

            }
            else
            {
                if (total_tiles == 0)
                {
                    empty_space[0] = i;
                    empty_space[1] = j;
                }
                board[i][j] = total_tiles;
            }

            if (total_tiles > 0)
            {
               total_tiles--;
            }

        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            int tile_val = board[i][j];
            if (tile_val > 9)
            {
                printf(" %i", board[i][j]);
            }
            else
            {
                printf("  %i", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // loop over 2-d board and find the tile sequence
    // corresponding to 'tile' (i.e. 2, 1).
    int tile_position[2];
    get_tile_position(tile_position, tile);

    // look at where the 'empty space' is (ie 2, 2)
    // one of either i or j must be the same as that of
    // the empty space. If the other value is either 1
    // less or one more, it is valid to move.
    bool i_equal = tile_position[0] == empty_space[0];
    bool j_equal = tile_position[1] == empty_space[1];


    if (i_equal && !j_equal)
    {
        return handle_switch_tiles(1, tile_position, tile);
    }

    if (j_equal && !i_equal)
    {
        return handle_switch_tiles(0, tile_position, tile);
    }

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    int counter = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            int target = board[i][j];
            if (target != counter && target != 0)
            {
                return false;
            }
            counter++;
        }
    }
    return true;
}

void print_empty(void)
{
    printf("Empty space tracker:");
    for (int i = 0; i < 2; i++)
    {
        printf(" %i", empty_space[i]);
    }
    printf("\n");
}

void get_tile_position(int tile_position[], int tile)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                tile_position[0] = i;
                tile_position[1] = j;
            }
        }
    }
}

bool handle_switch_tiles(int idx, int tile_position[], int tile)
{
    int eval_positions = tile_position[idx] - empty_space[idx];
    if (eval_positions == 1 || eval_positions == -1)
    {
        // switch the tiles
        board[tile_position[0]][tile_position[1]] = 0;
        board[empty_space[0]][empty_space[1]] = tile;
        // store the indexes of the empty space
        empty_space[0] = tile_position[0];
        empty_space[1] = tile_position[1];
        // valid move
        return true;
    }
    return false;
}
