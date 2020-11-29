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
    // Initialize head pointer
    node *head = NULL;

    // Initialize buffer variable
    char dictionaryWord[LENGTH];

    // Initialize count variable
    int wordCount = 0;

    // Open Dictionary File
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return false;
    }

    // While scanf != EOF, scan opened dictionary file
    // do
    // {
    fscanf(file, "%s", dictionaryWord);
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
    head = wordList;

    fscanf(file, "%s", dictionaryWord);
    // Allocate Memory
    wordList = malloc(sizeof(node));

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
    head->next = wordList;

    // Handle assignment of head pointer
    // if (head == NULL)
    // {
    //     head = wordList;
    //     printf("%s\n", head->word);
    //     // head->next = wordList;
    //     // head = ->word;
    // }
    // else
    // {
    //     printf("else\n");
    //     wordList->next = head;

    //     // Handle insertion of new nodes
    //     // for (node *new_node = wordList; new_node == NULL; new_node = new_node->next)
    //     // {
    //         // ...toDo
    //     // }
    // }

    // while (fscanf(file, "%s", dictionaryWord) != EOF);

    // for (node *new_node = wordList; new_node == NULL; new_node = new_node->next)
    // {
    //     printf()
    // }

    // Call hash function
    // table[hash(wordList->word)] = head;

    // printf("%s\n", table[0]->word);

    // }

    // Read scanned and copied words using tmp variable loop
    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        printf("%s\n", tmp->word);
    }

    // Free allocated memory
    while (head != NULL)
    {
        node *tmp = head->next;
        free(head);
        head = tmp;
    }
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
