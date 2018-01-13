#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string s = get_string();
    int n = 0;
    while (s[n] != '\0') // This is sort of like C's way of implementing a 'period' in memory
    { //is the nth char this special characters? One byte of all zeros.
        n++;
    }
    printf("The length of the string is %i", n);
}