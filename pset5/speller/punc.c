#include <stdbool.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char *word = "inductor's";
    printf("%s\n", word);
    printf("%c\n", word[8]);
    printf("as int: %i\n", word[8]);
    bool alpha = isalpha(word[8]);
    bool alpha_check = isalpha(word[6]);
    if (alpha_check)
    {
        printf("yes\n");
    }
    if (!alpha)
    {
        printf("aposto\n");
    }

    char *test = "Peter.";
    bool period_test = isalpha(test[5]);
    if (period_test)
    {
        printf("periods are alphanumeric?\n");
    }
    if (!period_test)
    {
        printf("periods are not alphanumeric\n");
    }
}