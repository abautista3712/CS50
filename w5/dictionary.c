// Implements a dictionary's functionality

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 27;

// Initialize Word Count Variable
int wordCount = -1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    for (node *cursor = table[hash(word)]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            // printf("MATCH: %s\n", cursor->word);
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // int hashNum = (int) word[0];
    // if()
    // {
    //     return
    // }

    int firstLetter = (int)word[0];

    if (firstLetter >= 97 && firstLetter <= 122)
    {
        firstLetter = (firstLetter - 96);
        return firstLetter;
    }
    else if (firstLetter >= 65 && firstLetter <= 90)
    {
        firstLetter = (firstLetter - 64);
        return firstLetter;
    }
    else
    {
        return 0;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize variables
    char dictionaryWord[LENGTH] = "";
    *table = NULL;
    int hashInt = 0;

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
            wordCount++;
        }
        else
        {
            node *new_node = wordList;
            wordList->next = table[hashInt];
            table[hashInt] = wordList;
            wordCount++;
        }
    }

    while (fscanf(file, "%s", dictionaryWord) != EOF);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    printf("Words Counted: %i\n", wordCount);
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 27; i++)
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
