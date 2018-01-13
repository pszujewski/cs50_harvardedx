#include <cs50.h>
#include <stdio.h>

int get_water_amount();

int main(void)
{
    printf("Input how long your shower is (minutes):\n");
    int amt = get_water_amount();
    printf("Amount of water used for your shower is: %i\n", amt);

}

int get_water_amount(void)
{
    int minutes = get_int();
    return minutes * 12;
}