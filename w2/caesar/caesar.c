#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handleUppercase(int key, string strPlaintext, int j);
void handleLowercase(int key, string strPlaintext, int j);

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
    int key = atoi(argv[1]) % 26;
    printf("Key = %i\n", key);
    string strPlaintext = get_string("plaintext: ");

    for (int j = 0, m = strlen(strPlaintext); j < m; j++)
    {
        if (strPlaintext[j] >= 65 && strPlaintext[j] <= 90)
        {
            handleUppercase(key, strPlaintext, j);
        }
        else if (strPlaintext[j] >= 97 && strPlaintext[j] <= 121)
        {
            handleLowercase(key, strPlaintext, j);
        }
    }

    printf("\n");
}

void handleUppercase(int key, string strPlaintext, int j)
{
    // for (int k = 0, p = strlen(strPlaintext); k < p; k++)
    // {
    int intPlaintext = (int)strPlaintext[j];
    int intCiphertext = intPlaintext + key;
    if (intCiphertext > 90)
    {
        intCiphertext = 64 + (90 - intPlaintext) + key;
        printf("%c", (char)intCiphertext);
    }
    else
    {
        printf("%c", (char)intCiphertext);
    }
    // }
}

void handleLowercase(int key, string strPlaintext, int j)
{
    // for (int l = 0, q = strlen(strPlaintext); l < q; l++)
    // {
    int intPlaintext = (int)strPlaintext[j];
    int intCiphertext = intPlaintext + key;
    if (intCiphertext > 122)
    {
        intCiphertext = 97 + (122 - intPlaintext) + key;
        printf("%c", (char)intCiphertext);
    }
    else
    {
        printf("%c", (char)intCiphertext);
    }
    // }
}