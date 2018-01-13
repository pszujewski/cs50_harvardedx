#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(int src[], int len);

int main(void)
{
    int res = 1 + 1;
    printf("%i", 2 / 2);
}

void print_array(int src[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", src[i]);
    }
    printf("\n");
}