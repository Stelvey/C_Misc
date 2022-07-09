// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


// Custom prototypes & global variables
unsigned int concatenate(unsigned x, unsigned y);
unsigned amount = 0;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 200000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    if (table[hash(word)] != NULL)
    {
        // Traverse the linked list
        for (node *p = table[hash(word)]; p != NULL; p = p->next)
        {
            // Compare strings
            if (strcasecmp(word, p->word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    char hash_string[LENGTH + 1];
    unsigned hash = 0;

    // Concatenate ASCIIs of capitalized chars
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = concatenate(hash, (int)toupper(word[i]));
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH + 1];

    //Opens a dictionary
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }

    // Reads a word
    while (fscanf(input, "%s", word) != EOF)
    {
        // Allocates a node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copies a word to a node
        strcpy(n->word, word);

        // Inserts a node at the beginning of a list
        n->next = table[hash(n->word)];
        table[hash(n->word)] = n;

        //Count words, size() will return this
        amount++;
    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return amount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i != N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}

// Custom: appends number Y to number X
unsigned int concatenate(unsigned x, unsigned y)
{
    unsigned pow = 10;
    while (y >= pow)
    {
        pow *= 10;
    }
    return x * pow + y;
}