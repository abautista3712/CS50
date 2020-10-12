#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void countLetters(string inputText);
void countWords(string inputText);
void countSentences(string inputText);

int main(void)
{
    string inputText = get_string("Text: ");
    countLetters(inputText);
    countWords(inputText);
    countSentences(inputText);
}

void countLetters(string inputText)
{
    int letters = 0;
    for (int i = 0, n = strlen(inputText); i < n; i++)
    {
        if (isalnum(inputText[i]))
        {
            letters++;
        }
    }
    printf("Letters: %i\n", letters);
}

void countWords(string inputText)
{
    int words = 0;
    if (isalnum(inputText[0]))
    {
        words = 1;
    }
    for (int i = 0, n = strlen(inputText); i < n; i++)
    {
        if (isspace(inputText[i]))
        {
            words++;
        }
    }
    printf("Words: %i\n", words);
}

void countSentences(string inputText)
{
    int sentences = 0;
    for (int i = 0, n = strlen(inputText); i < n; i++)
    {
        if (inputText[i] == '.' | inputText[i] == '!' | inputText[i] == '?')
        {
            sentences++;
        }
    }
    printf("Sentences: %i\n", sentences);
}