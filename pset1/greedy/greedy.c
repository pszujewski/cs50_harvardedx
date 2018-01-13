#include <cs50.h>
#include <stdio.h>
#include <math.h>

int get_and_convert(void);
bool eval_coin_type(int coin_type, int change, int total_change_needed, bool hasCoin);

int main(void)
{
    int total_change_needed = get_and_convert();

    int change = 0;
    int total_coins_needed = 0;

    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    while (change < total_change_needed)
    {

        bool hasCoin = false;

        bool eval_quarter = eval_coin_type(quarter, change, total_change_needed, hasCoin);
        if (eval_quarter)
        {
            change += quarter;
            hasCoin = true;
        }

        bool eval_dime = eval_coin_type(dime, change, total_change_needed, hasCoin);
        if (eval_dime)
        {
            change += dime;
            hasCoin = true;
        }

        bool eval_nickel = eval_coin_type(nickel, change, total_change_needed, hasCoin);
        if (eval_nickel)
        {
            change += nickel;
            hasCoin = true;
        }

        bool eval_penny = eval_coin_type(penny, change, total_change_needed, hasCoin);
        if (eval_penny)
        {
            change += penny;
            hasCoin = true;
        }

        total_coins_needed++;
        // printf("Change is currently at: %i\n", change);
    }

    // printf("Change is equal to: %i\n", change);
    // printf("TOTAL COINS NEEDED: %i\n", total_coins_needed);
    printf("%i\n", total_coins_needed);
}

int get_and_convert(void)
{
    printf("O hai! How much change is owed?\n");
    float input = get_float();
    printf("input: %f\n", input);
    float converter = input * 100;
    printf("converter: %f\n", converter);

    // a double is a float
    double rounded = roundf(converter);
    //printf("rounded: %f\n", rounded);

    int total_change_needed = (int) rounded;
    printf("total needed %i\n", total_change_needed);

    if (total_change_needed < 0)
    {
        printf("Oooops. Negative number. Try again.\n");
        return get_and_convert();
    }
    return total_change_needed;
}

bool eval_coin_type(int coin_type, int change, int total_change_needed, bool hasCoin)
{
    if (hasCoin)
    {
        return false;
    }
    else
    {
        bool eval = coin_type + change <= total_change_needed;
        return eval;
    }
}


