#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void handleCipher(string plaintext, string key);
int caseInsensitive(int intSearchTerm);
int encryptPlaintext(int intPlaintext, string key);

int main(int argc, string argv[])
{
    // Error is given if there are not two command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Specifications on second command-line argument
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // If key is not alphabetical, give error
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        // If key is not 26 characters long, give error
        else if (n != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    // Set variables for key and plaintext
    string key = argv[1];
    string plaintext = get_string("plaintext: ");
    // Print on output line
    printf("ciphertext: ");
    // Run handleCipher function
    handleCipher(plaintext, key);
}

// Function to handle looping through plaintext characters
void handleCipher(string plaintext, string key)
{
    // Loop through every character of plaintext
    for (int j = 0, o = strlen(plaintext); j < o; j++)
    {
        // If character is alphabetical, continue to encrypt based on key
        if (isalpha(plaintext[j]))
        {
            int intPlaintext = (int)plaintext[j];
            int intCiphertext = encryptPlaintext(intPlaintext, key);
            printf("%c", (char)intCiphertext);
        }
        // If character is non-alphabetical, print as is
        else
        {
            printf("%c", (char)plaintext[j]);
        }
    }
    printf("\n");
}

// Function to ignore case for encryption purposes
int caseInsensitive(int intSearchTerm)
{
    // If ASCII code is between 97 and 122, subtract 97 to locate array position in key
    if (intSearchTerm >= 97 && intSearchTerm <= 122)
    {
        intSearchTerm -= 97;
    }
    // If ASCII code is between 65 and 90, subtract 65 to locate array position in key
    else if (intSearchTerm >= 65 && intSearchTerm <= 90)
    {
        intSearchTerm -= 65;
    }
    return intSearchTerm;
}

// Function that converts plaintext to ciphertext and replaces original case
int encryptPlaintext(int intPlaintext, string key)
{
    // Register if original plaintext character is upper or lower case
    bool isPlaintextUppercase = false;
    if (intPlaintext >= 65 && intPlaintext <= 90)
    {
        isPlaintextUppercase = true;
    }
    // Remove case temporarily to encrypt based on key
    int ci_intPlaintext = caseInsensitive(intPlaintext);
    // Convert plaintext to ciphertext still ignoring case
    int ci_intCiphertext = caseInsensitive(key[ci_intPlaintext]);
    // Replace original case
    int intCiphertext = ci_intCiphertext;
    isPlaintextUppercase ? (intCiphertext += 65) : (intCiphertext += 97);
    return intCiphertext;
}