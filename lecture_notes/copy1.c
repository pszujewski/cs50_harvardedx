#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    printf("s: ");
    // the way you type out the address of a char is 'char *'
    // char * is identical to 'string'
    char *s = get_string();

    if (s == NULL)
    {
        // error code
        return 1;
    }

    // malloc returns a pointer to contiguous
    // block of memory that is 7 bytes here.
    char *t = malloc(7);

    if (t == NULL)
    {
        return 1;
    }

    for (int i = 0, n = strlen(s); i <= n; i++ )
    {
        // copy the ith character into corresponding slot in
        // our chunk of memory we got back.
        // s contains the address of the string
        // t contains the address of the memory chunk we got.
        t[i] = s[i];
    }

    if (strlen(t) > 0)
    {
        // we are actually changing different memory here
        // different memory address. We avoid the side-effect because
        // we are working with different chunks of memory.
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);

    // success
    return 0;
}