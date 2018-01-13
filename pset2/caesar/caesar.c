#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int cipher(char c, int k);
bool is_in_range(bool is_upper_case, int ascii);
bool is_alphabetical(char c);
int apply_offset(bool is_upper, int ciphered_val);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // return a 1 error code if user does not provide command-line argument
        return 1;
    }

    // convert the user's input from str to int
    int k = atoi(argv[1]);

    printf("plaintext: ");
    string plain = get_string();

    printf("\n");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plain); i < n; i++)
    {
       // test if the current character in this iteration is indeed a alphabetical letter
       bool is_letter = is_alphabetical(plain[i]);
       if (!is_letter)
       {
           // non-alphabetical letters are printed to the screen unchanged
           printf("%c", plain[i]);
       }
       else
       {
           // Apply the cipher here
           printf("%c", cipher(plain[i], k));
       }
    }
    printf("\n");
    return 0;
}

bool is_alphabetical(char c)
{
    // cast the char as an int
    int ascii = (int) c;
    // test the int against the ranges for letters in ascii
    bool upper_alpha = ascii >= 65 && ascii <= 90;
    bool lower_alpha = ascii >= 97 && ascii <= 122;
    if (upper_alpha || lower_alpha)
    {
        // character would be in range of letters in ascii
        return true;
    }
    return false;
}

bool is_in_range(bool is_upper_case, int ascii)
{
    if (is_upper_case)
    {
        return ascii >= 65 && ascii <= 90;
    }
    return ascii >= 97 && ascii <= 122;
}

int apply_offset(bool is_upper, int ciphered_val)
{
    int offset;
    if (is_upper)
    {
       // the first ascii for upper case letters ('A')
       offset = 65;
    }
    else
    {
       // the first ascii for lower case letters ('a')
       offset = 97;
    }
    // apply the mod operation below to find how many spots passed the range
    // the ciphered_val is located. There are 26 spots in the both upper case and
    // lower case ranges. How many more than 26 is the ciphered_val after offset
    // is applied?
    int moded = (ciphered_val - offset) % 26;
    // re-apply the offset so the ascii value is back within the correct range
    // depending on whether its upper or lower case.
    return moded + offset;
}

int cipher(char c, int k)
{
    bool is_upper = isupper(c);
    // cast the char as an int
    int ascii_val = (int) c;
    // apply the cipher secret key provided by the user ('k')
    // then check to make sure the 'ciphered' char
    // corresponds to an ascii value still in the
    // correct range (depends on if its upper case or lower case)
    int ciphered_val = ascii_val + k;
    // Need to be sure the ciphered_val has not exceeded
    // the bounds of either upper or lower case ranges
    bool range_test = is_in_range(is_upper, ciphered_val);
    if (!range_test)
    {
      // We need to apply an offset that will wrap
      // the ciphered_val back to the start of the range
      return apply_offset(is_upper, ciphered_val);
    }
    // otherwise, ciphered_val is in range still so just return it.
    return ciphered_val;
}