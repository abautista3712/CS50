#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int countLetters(string inputText);
int countWords(string inputText);
int countSentences(string inputText);
void colemanLiauIndex(int letters, int words, int sentences);

int main(void)
{
    string inputText = get_string("Text: ");
    int letters = countLetters(inputText);
    int words = countWords(inputText);
    int sentences = countSentences(inputText);
    colemanLiauIndex(letters, words, sentences);
}

int countLetters(string inputText)
{
    int letters = 0;
    for (int i = 0, n = strlen(inputText); i < n; i++)
    {
        if (isalnum(inputText[i]))
        {
            letters++;
        }
    }
    // printf("Letters: %i\n", letters);
    return letters;
}

int countWords(string inputText)
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
    // printf("Words: %i\n", words);
    return words;
}

int countSentences(string inputText)
{
    int sentences = 0;
    for (int i = 0, n = strlen(inputText); i < n; i++)
    {
        if (inputText[i] == '.' | inputText[i] == '!' | inputText[i] == '?')
        {
            sentences++;
        }
    }
    // printf("Sentences: %i\n", sentences);
    return sentences;
}

void colemanLiauIndex(int letters, int words, int sentences)
{
    float L = (letters / (float)words) * 100;
    float S = (sentences / (float)words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}