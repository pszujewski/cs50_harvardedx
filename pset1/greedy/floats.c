#include <cs50.h>
#include <stdio.h>

// https://cs50.stackexchange.com/questions/4584/cant-cast-a-float-to-an-int/4585

int main(void)
{
    float test = 1.0 / 3.0;
    float test2 = 1.0 / 10.0;

    printf("Input a real number with a decimal number %f\n", test - test2);
    float res = get_float();

    // convert float to int
    float converter = res * 100;
    int change_needed = (int) converter;

    printf("Change needed is %i\n", change_needed);
}