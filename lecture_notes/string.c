#include <cs50.h>
#include <stdio.h>
#include <string.h>

// strlen returns the length of the string

int main(void)
{
    string s = get_string();
    printf("The string is %s\n", s);

    if (s != NULL) // NULL is a 'special value in C' Notice that not equals is !=, not with 2 equals.
    { // since we a re checking for null, this will never crash. It will return null if string is way too long for example
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            printf("%c\n", s[i]);
        }
    }
}