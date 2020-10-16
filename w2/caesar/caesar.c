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
    // Encryption will only change within alphabetical characters
    int key = atoi(argv[1]) % 26;
    // Ask for user input for plaintext
    string strPlaintext = get_string("plaintext: ");
    // Check each character from the beginning to the end of the string length
    for (int j = 0, m = strlen(strPlaintext); j < m; j++)
    {
        // If uppercase alphabetical character, use handleUppercase function
        if (strPlaintext[j] >= 65 && strPlaintext[j] <= 90)
        {
            handleUppercase(key, strPlaintext, j);
        }
        // If lowercase alphabetical character, use handleUppercase function
        else if (strPlaintext[j] >= 97 && strPlaintext[j] <= 121)
        {
            handleLowercase(key, strPlaintext, j);
        }
    }
    printf("\n");
}

// Function to handle uppercase characters
void handleUppercase(int key, string strPlaintext, int j)
{
    int intPlaintext = (int)strPlaintext[j];
    int intCiphertext = intPlaintext + key;
    // If intPlaintext + key = character ASCII code past uppercase Z, start from uppercase A
    if (intCiphertext > 90)
    {
        intCiphertext = 64 + (90 - intPlaintext) + key;
        printf("%c", (char)intCiphertext);
    }
    // Else use intPlaintext + key
    else
    {
        printf("%c", (char)intCiphertext);
    }
}

// Function to handle lowercase characters
void handleLowercase(int key, string strPlaintext, int j)
{
    int intPlaintext = (int)strPlaintext[j];
    int intCiphertext = intPlaintext + key;
    // If intPlaintext + key = character ASCII code past lowercase z, start from lowercase a
    if (intCiphertext > 122)
    {
        intCiphertext = 97 + (122 - intPlaintext) + key;
        printf("%c", (char)intCiphertext);
    }
    // Else use intPlaintext + key
    else
    {
        printf("%c", (char)intCiphertext);
    }
}