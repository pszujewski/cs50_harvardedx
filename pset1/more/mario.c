#include <cs50.h>
#include <stdio.h>

int get_row_spec();
void mario_pyramid(int h);
void print_half_row(int n, int half_row, bool isSecond);
void print_spaces(int n);
void print_hashes(int n);

int main(void)
{
    int h = get_row_spec();
    if (h > 0)
    {
        mario_pyramid(h);
    }
}

int get_row_spec()
{
    printf("Input a height for the half-pyramid\n");
    int h = get_int();
    if (h <= 23 && h > 0)
    {
        return h;
    }
    else
    {
        printf("Please input an integer between 1 and 23\n");
        return 0;
    }
}

void mario_pyramid(int h)
{
   for (int i = 1; i <= h; i++)
    {
        print_half_row(i, h, false);
        print_spaces(2);
        print_half_row(i, h, true);
        printf("\n");
    }
}

void print_half_row(int n, int half_row, bool isSecond)
{
    int spaces = half_row - n;
    if (isSecond)
    {
        print_hashes(n);
        print_spaces(spaces);
    }
    else
    {
        print_spaces(spaces);
        print_hashes(n);
    }
}

void print_spaces(int n)
{
   for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

void print_hashes(int n)
{
   for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}


