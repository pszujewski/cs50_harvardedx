#include <cs50.h>
#include <stdio.h>

// explicit casting example, with parens and the name of the data type you want to convert to.
// remember that chars use single quotes.

int main(void)
{
    for (int i = 0; i < 65 + 26; i++)
    {
        printf("%c is %i\n", (char) i, i); // convert integer to char. although this isn't explicity necessary.
    }   // you say in the formatting string that you want a char, so printf takes the int and converts it to a char.

    // since chars are really just numbers, you can iterate over chars
    for (char c = 'A'; c <= 'Z'; c++)
    {
        printf("%c is expressed as this int: %i\n", c, (int) c); // explicit casting
        // printf("%c is %i", c, c); // C would convert it thanks to formatiing in the string of printf
    }

}