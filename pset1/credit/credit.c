#include <cs50.h>
#include <stdio.h>

// Example: 378282246310005
// 4111111111111111
// 5467904671708277

bool isVisa(int first_number);

int main(void)
{
    printf("Please Enter a CC number\n");

    long cc_number = get_long_long();
    int sum = 0;
    int odd_sum = 0;
    int counter = 0;
    int first_number = 0;
    while (cc_number > 0)
    {
        counter += 1;
        int last_number = cc_number % 10;
        if (counter % 2 == 0)
        {
            int result = last_number * 2;
            // printf("result: %i\n", result);
            while (result > 10)
            {
                int last = result % 10;
                //printf("greater than 10, so last: %i\n", last);
                sum += last;
                result /= 10;
            }
            //printf("adding result as follows TO sum: %i\n", result);
            sum += result;
        }
        else
        {
            odd_sum += last_number;
        }
        cc_number /= 10;
        if (cc_number == 0 || cc_number < 0)
        {
            first_number = last_number;
        }
    }

    int total = odd_sum + sum;
    int check = total  % 10 == 0;
    //printf("The total is: %i\n", total);

    if (check)
    {
        switch(counter)
        {
            case 13:
                printf("VISA\n");
                break;
            case 15:
                printf("AMEX\n");
                break;
            case 16:
                if (isVisa(first_number))
                {
                  printf("VISA\n");
                  break;
                }
                printf("MASTERCARD\n");
                break;
            default:
                printf("UKNOWN\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

bool isVisa(int first_number)
{
    return first_number == 4;
}
