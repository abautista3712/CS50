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
    // int hashNum = (int) word[0];
    // printf("Word: %s\nHash Num: %i\n", word, hashNum);

    // return hashNum;
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize variables
    char dictionaryWord[LENGTH] = "";
    *table = NULL;
    int hashInt = 0;
    int wordCount = 0;

    // Open Dictionary File
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return false;
    }

    // While scanf != EOF, scan opened dictionary file
    do
    {
        // Allocate Memory
        node *wordList = malloc(sizeof(node));

        // End loading if no memory is available to allocate
        if (wordList == NULL)
        {
            return false;
        }

        // Assign node values:
        // 1) Copy scanned string into node 'word'
        strcpy(wordList->word, dictionaryWord);
        // 2) Set node 'next' default value
        wordList->next = NULL;

        hashInt = hash(wordList->word);

        // Handle assignment of head pointer
        if (table[hashInt] == NULL)
        {
            table[hashInt] = wordList;
        }
        else
        {
            node *new_node = wordList;
            wordList->next = table[hashInt];
            table[hashInt] = wordList;
        }
    } while (fscanf(file, "%s", dictionaryWord) != EOF);

    // Read scanned and copied words using tmp variable loop
    for (node *tmp = table[hashInt]; tmp != NULL; tmp = tmp->next)
    {
        printf("table[%i]\n", hashInt);
        printf("%s\n", tmp->word);
        wordCount++;
    }

    // Free allocated memory
    while (table[hashInt] != NULL)
    {
        node *tmp = table[hashInt]->next;
        free(table[hashInt]);
        table[hashInt] = tmp;
    }

    printf("Word Count: %i\n", wordCount - 1);

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
