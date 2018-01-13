#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[]) // argc stands for 'argument count' the number of args provided to the program
{   // it is only 1 if you just run ./file

    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]); // print out the i-th string in the array.
    }

    if (argc == 2)
    {
        printf("hello, %s\n", argv[1]);
    }
    else
    {
       printf("hello, world\n");
    }
}