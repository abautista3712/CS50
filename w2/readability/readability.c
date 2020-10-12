#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int characters = 0;
    string inputText = get_string("Text: ");
    for (int i = 0, n = strlen(inputText); i < n; i++)
    {
        characters++;
    }
    printf("%i\n", characters);
}