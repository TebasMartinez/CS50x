// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 27;

// Hash table
node *table[N];

// Words counter
int wordcount = 0;

// Is dictionary loaded?
bool loaded = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashvalue = hash(word);
    for (node *ptr = table[hashvalue]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (isalpha(word[0]) == 0)
    {
        return N;
    }
    else
    {
        return toupper(word[0]) - 'A';
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }
    // Read strings from file one at a time
    char buffer[LENGTH + 1];

    while (fscanf(dic, "%s", buffer) != EOF)
    {
        // Create a new node for each word
        node *newword = malloc(sizeof(node));
        if (newword == NULL)
        {
            return false;
        }
        newword->next = NULL;

        // Copy the word
        strcpy(newword->word, buffer);

        // Hash word to obtain a hash value
        int hashvalue = hash(newword->word);

        // Insert node into hash table at that location
        // If the location already has words
        if (table[hashvalue] != NULL)
        {
            newword->next = table[hashvalue];
            table[hashvalue] = newword;
            wordcount++;
        }
        else
        {
            table[hashvalue] = newword;
            wordcount++;
        }
    }

    // Close the dictionary
    fclose(dic);

    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    if (loaded == true)
    {
        for (int i = 0; i < N; i++)
        {
            for (node *ptr = table[i]; ptr != NULL;)
            {
                node *tmp = ptr;
                ptr = ptr->next;
                free(tmp);
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
