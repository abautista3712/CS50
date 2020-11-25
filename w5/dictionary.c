// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize head pointer
    node *head = NULL;

    // Allocate Memory
    node *wordList = malloc(sizeof(node));

    // End loading if no memory is available to allocate
    if (wordList == NULL)
    {
        return false;
    }

    // Open Dictionary File
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return false;
    }

    // Initialize buffer variable
    char dictionaryWord[LENGTH];

    do
    {
        // Scan opened dictionary file
        fscanf(file, "%s", dictionaryWord);

        // Assign node values
        // 1) Copy scanned string into node 'word'
        strcpy(wordList->word, dictionaryWord);
        // 2) Set node 'next' default value
        wordList->next = NULL;

        // Call hash function
        hash(wordList->word);

        // Handle insertion of new nodes
        for (node *new_node = wordList; new_node != NULL; new_node = new_node->next)
        {
            printf("%s\n", wordList->word);
        }
    }

    while (fscanf(file, "%s", dictionaryWord) != EOF);

    free(wordList);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
