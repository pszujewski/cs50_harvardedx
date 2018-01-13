/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */

#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // if the argument count is not 2 or 3
    // we remind the user of the program's
    // usage and return a '1' error code.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // Access the required command-line argument provided
    // by the user at index position 1 of the argument vector
    // parameter. This item is a string but we need an integer
    // so we convert the item from str to int using the
    // library function atoi()
    // this indicates the number of randm numbers you want in total
    int n = atoi(argv[1]);

    // srand is the initializer function for using drand. srand takes a long int
    // as its 'seedval.' If seedval is provided by the user, convert to int and input into
    // srand function
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        // just gets the time, this ensures we use a unique seedval in the event
        // a seedval ('s') is not given by the user.
        srand48((long) time(NULL));
    }

    // drand generates 'uniformly distributed pseudo-random numbers'
    // srand48 should be called before using this function
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
