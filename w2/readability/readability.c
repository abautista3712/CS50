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
    // Ask for user input for text to analyze
    string inputText = get_string("Text: ");
    // Count number of letters and save to variable
    int letters = countLetters(inputText);
    // Count number of words and save to variable
    int words = countWords(inputText);
    // Count number of sentences and save to variable
    int sentences = countSentences(inputText);
    // Plug-in letters, words, and sentences into Coleman-Liau Index calculation
    colemanLiauIndex(letters, words, sentences);
}

// Function to count letters
int countLetters(string inputText)
{
    // Initialize variable 'letters' to 0
    int letters = 0;
    // Loop through each character of input text until the length of the string. Add one to 'letters' variable for each character.
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

// Function to count words
int countWords(string inputText)
{
    // Initialize variable 'words' to 0
    int words = 0;
    // If the first character of the input text is alpha-numeric, change word count to 1
    if (isalnum(inputText[0]))
    {
        words = 1;
    }
    // Loop through input text and add one to 'words' variable for each white space
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

// Function to count sentences
int countSentences(string inputText)
{
    // Initialize variable 'sentences' to 0
    int sentences = 0;
    // Loop through input text and add one to 'sentences' variable for each '.', '!', '?'
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

// Function to calculate Coleman-Liau Index
void colemanLiauIndex(int letters, int words, int sentences)
{
    // Calculate letters per 100 words
    float L = (letters / (float)words) * 100;
    // Calculate sentences per 100 words
    float S = (sentences / (float)words) * 100;
    // Colman-Liau Index Calcuation
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    // Special cases
    // (1) Grade 16+
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    // (2) Before Grade 1
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    // Regular cases
    else
    {
        printf("Grade %i\n", index);
    }
}