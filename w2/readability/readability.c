#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void countLetters(string inputText);

int main(void)
{
    string inputText = get_string("Text: ");
    countLetters(inputText);
}

void countLetters(string inputText)
{
    int letters = 0;
    for (int i = 0, n = strlen(inputText); i < n; i++)
    {
        if (isalpha(inputText[i]) | isdigit(inputText[i]))
        {
            letters++;
        }
    }
    printf("%i\n", letters);
}