#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SPACE 32
#define ASCIINULL 0

bool is_space(char c);
bool null_test(char n);
bool is_valid(int i, int n);
void print_next_val(string str, int idx, int len);

int main(void)
{
    // get the string from the user and find the string's length
    string s = get_string();
    int n = strlen(s);

    // iterate over each char of the string
    for (int i = 0; i < n; i++)
    {
        char current = s[i];
        bool space = is_space(current);
        bool valid_idx = is_valid(i, n);
        // Always print the very first char in the string unless it is a space
        if (i == 0 && !space)
        {
            printf("%c", toupper(s[i]));
        }
        // for all chars other than the very first in the string
        else if (space && valid_idx && i != 0)
        {
            // print the next char in string since it is part of initials
            print_next_val(s, i, n);
        }
    }
    printf("\n");
}

bool is_space(char c)
{
    // space means new part of name.
    // find the ascii value of the current char
    int ascii = (int) c;
    return ascii == SPACE;
}

// Don't allow if the very last char in string is a space
bool is_valid(int i, int n)
{
    return i != n;
}

bool null_test(char c)
{
    int ascii = (int) c;
    return ascii == ASCIINULL;
}

void print_next_val(string str, int idx, int len)
{
    // the next char in str is position + 1
    char next = str[idx + 1];
    // Don't print spaces
    if (!is_space(next) && is_valid(idx, len) && !null_test(next))
    {
        printf("%c", toupper(next));
    }
}