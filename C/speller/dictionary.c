// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 100000;

node *table[N];

int dict_num = 0;

// hash function, takes an word as an input, store the outputs in bucket
unsigned int hash(const char *word)
{
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// take dictionary, load it into a hash table
bool load(const char *dictionary)
{
    // open the file: dictionary
    FILE *dict_pointer = fopen(dictionary, "r");
    // check if the file can be opened
    if (dictionary == NULL)
    {
        printf("Cannot open the file.");
        return false;
    }

    // define a temp array to store the data before add to the hash table
    char the_next_word[LENGTH + 1];

    // scan the data of the dictionary until end of the file
    while (fscanf(dict_pointer, "%s", the_next_word) != EOF)
    {
        // crate the new node for each word to store
        node *n = malloc(sizeof(node));
        // check if the memory is enough
        if (n == NULL)
        {
            printf("Out of memory.");
            return false;
        }

        else
        {
            // copy the word from dictionary to new node by using stycpy
            strcpy(n->word, the_next_word);
            // Obtain the value from hash function
            int hash_value = hash(the_next_word);
            // point to the hash table at that location
            n->next = table[hash_value];
            table[hash_value] = n;
            dict_num ++;
        }
    }
    // close the file
    fclose(dict_pointer);
    return true;
}

unsigned int size(void)
{
    // returns the numbers of dictionary
    return dict_num;
}

bool check(const char *word)
{
    // obtain hash value
    int hash_value = hash(word);
    // create the cursor to traverse the linked list
    node *cursor = table[hash_value];
    while (cursor != NULL)
    {
        // use strcasecmp to check whether the word is in the dictionary
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// freeing linked list
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // create the temp cursor to point the word
        node *cursor = table[i];
        while (cursor != NULL)
        {
            // create the temp node to point the cursor, prevent losing the access to the rest
            node *tmp = cursor;
            // move the cursor to the next word
            cursor = cursor->next;
            // free the memory of temp word
            free(tmp);
        }

        // if end of the cursor, return
        if (cursor == NULL && i + 1 == N)
        {
            return true;
        }
    }

    return false;
}
