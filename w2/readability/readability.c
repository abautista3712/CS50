#include <stdio.h>
#include <cs50.h>
#include <string.h>

void countLetters(string inputText);

int main(void)
{

    string inputText = get_string("Text: ");
    countLetters(inputText);
}

void countLetters(string inputText)
{
    int characters = 0;
    for (int i = 0, n = strlen(inputText); i < n; i++)
    {
        characters++;
    }
    printf("%i\n", characters);
}