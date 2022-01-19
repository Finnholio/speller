// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <stdint.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int length = strlen(word);
    char lword[length + 1];

    for (int i = 0; i < length; i++)
    {
        lword[i] = tolower(word[i]);
    }
    lword[length] = '\0';

    int index = hash(lword);
    node *currentNode = table[index];
    while (currentNode != NULL)
    {
        if (strcasecmp(currentNode->word, word) != 0)
        {
            currentNode = currentNode->next;
        }
        else
        {
            return true;
        }

    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    hash = word[0];

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false

bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");

    if(!f){
        return false;
    }

    char buffer[LENGTH + 1];

    while(fscanf(f, "%s", buffer) != EOF)
    {
        node *currentNode = malloc(sizeof(node));

        strcpy(currentNode->word, buffer);

        unsigned int index = hash(buffer);

        if(table[index] != NULL)
        {
           currentNode->next = table[index];
        }else {
            currentNode->next = NULL;
        }

        table[index] = currentNode;
    }

    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int sizeOfTable = 1;

    for (int i = 0; i < N; i++)
    {
        node *currentNode = table[i];
        while (currentNode->next != NULL)
        {
            sizeOfTable += 1;

            currentNode = currentNode->next;
        }
    }

    return sizeOfTable;
}

void destroy(node *root)
{
    if(root->next != NULL)
    {
        destroy(root->next);
    }

    free(root);

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if(table[i]!= NULL)
        {
            destroy(table[i]);
        }
    }

    return true;
}
