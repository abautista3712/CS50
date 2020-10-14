#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Produce error if not two command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Produce error if argv[1] contains anything but digit characters
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int key = atoi(argv[1]);
    printf("Key = %i\n", key);
    string inputText = get_string("plaintext: ");
    for (int j = 0, m = strlen(inputText); j < m; j++)
    {
        printf("%i\n", (int)inputText[j]);
    }
}