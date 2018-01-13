/**
 * Implements a dictionary's functionality.
 * https://stackoverflow.com/questions/5071796/string-literal-inside-struct-c
 */

#include <stdbool.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// define a node
typedef struct node
{
    char *word;
    struct node *next;
}
node;

// define an array of pointers to node structs
node *hashtable[27];

bool dictionaryIsLoaded = false;

// linked list and hashtable prototypes
int hash(char first_ltr);

bool search(char* word);

bool insert(char word[], int word_length);

void get_word(char original[], char target[], int word_length);

bool isSameStr(struct node *n, const char *search_term);

bool tableHasWord(struct node *n, const char *search_term);

void filter_word(const char *original, char target[], int word_length);

// Checks hashtable for a word
bool tableHasWord(struct node *n, const char *search_term)
{
    while (n != NULL)
    {
        if (isSameStr(n, search_term))
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// handles comparing char* (strings)
bool isSameStr(struct node *n, const char *search_term)
{
    //printf("%s\n", n->word);
    int n_len = strlen(n->word);
    int search_len = strlen(search_term);
    if (n_len != search_len)
    {
        return false;
    }
    for (int i = 0; i < n_len; i++)
    {
        if (toupper(n->word[i]) != toupper(search_term[i]))
        {
            return false;
        }
    }
    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    //printf("searching for %s\n", word);
    int length = strlen(word);
    char cpy_word[length];
    filter_word(word, cpy_word, length);

    int bucket = hash(cpy_word[0]);
    if (hashtable[bucket] == NULL)
    {
        //printf("No items in bucket\n");
        return false;
    }

    struct node *n = hashtable[bucket];
    //printf("%s\n", n->word);
    //printf("%s\n", n->word);
    if (tableHasWord(n, cpy_word))
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open up the dictionary read file
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        printf("No memory left\n");
        return false;
    }

    char word[LENGTH+1];
    int word_length = 0;

    for (int c = fgetc(dict_file); c != EOF; c = fgetc(dict_file))
    {
        if (c == '\n')
        {
            //printf("We have a space -> end word\n");

            char cpy_word[word_length];
            get_word(word, cpy_word, word_length);

            insert(cpy_word, word_length);

            word_length = 0;
        }
        else
        {
            //printf("%c\n", c);
            word[word_length] = c;
            word_length++;
        }
    }

    dictionaryIsLoaded = true;
    fclose(dict_file);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    int total = 0;
    if (!dictionaryIsLoaded)
    {
        return total;
    }

    for (int i = 0; i < 26; i++)
    {
        struct node *n = hashtable[i];
        while (n != NULL)
        {
            total++;
            n = n->next;
        }
    }
    return total;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        struct node *n = hashtable[i];
        while (n != NULL)
        {
            // keep the link to the next node
            struct node *tmp = n->next;
            // free the char* and then the whole node
            free(n->word);
            free(n);
            n = tmp;
        }
    }

    dictionaryIsLoaded = false;

    return true;
}

// linked-list functions

int hash(char first_ltr)
{
    // cast the char to its ascii int equivalents
    int ascii = (int) tolower(first_ltr);

    // 1 bucket per letter in alphabet. The last lowercase
    // ascii letter 'z' equals 122. The first 'a' is 97
    return (ascii >= 97) ? ascii - 97 : 26;
}

bool insert(char word[], int word_length)
{
   // call hash function to identify the bucket
   char first_ltr = word[0];
   int bucket = hash(first_ltr);

   //printf("word => %s\n", word);
   struct node *node_Ptr = malloc(sizeof(struct node));
   if (node_Ptr == NULL)
   {
       //printf("No more memory...\n");
       return false;
   }

   node_Ptr->next = NULL;
   node_Ptr->word = malloc(sizeof(char) * word_length + 1);
   strcpy(node_Ptr->word, word);

   //printf("res: %s\n", node_Ptr->word);

   // get the pointer for the bucket
   if (hashtable[bucket] != NULL)
   {
       node_Ptr->next = hashtable[bucket];
   }
   hashtable[bucket] = node_Ptr;
   return true;
}

void get_word(char original[], char target[], int word_length)
{
    int i = 0;
    while (i < word_length)
    {
        bool isltr = isalpha(original[i]);
        int ascii = (int) original[i];
        if (ascii == 39 || isltr)
        {
            target[i] = original[i];
            i++;
        }
    }
    target[i] = '\0';
}

void filter_word(const char *original, char target[], int word_length)
{
    int i = 0;
    while (i < word_length)
    {
        bool isltr = isalpha(original[i]);
        int ascii = (int) original[i];
        if (ascii == 39 || isltr)
        {
            target[i] = original[i];
            i++;
        }
    }
    target[i] = '\0';
}