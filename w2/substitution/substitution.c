#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void handleCipher(string plaintext);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        else if (n != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    string plaintext = get_string("plaintext: ");
    handleCipher(plaintext);
}

void handleCipher(string plaintext)
{
    for (int j = 0, o = strlen(plaintext); j < o; j++)
    {
        int intPlaintext = (int)plaintext[j];
        printf("%i\n", intPlaintext);
    }
}