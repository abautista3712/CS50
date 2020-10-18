#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void handleCipher(string plaintext, string key);
int caseInsensitive(int intSearchTerm);
int encryptPlaintext(int intPlaintext, string key);

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
    string key = argv[1];
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    handleCipher(plaintext, key);
}

void handleCipher(string plaintext, string key)
{
    for (int j = 0, o = strlen(plaintext); j < o; j++)
    {
        int intPlaintext = (int)plaintext[j];
        int intCiphertext = encryptPlaintext(intPlaintext, key);
        printf("%c", (char)intCiphertext);
    }
    printf("\n");
}

int caseInsensitive(int intSearchTerm)
{
    if (intSearchTerm >= 97 && intSearchTerm <= 122)
    {
        intSearchTerm -= 97;
    }
    else if (intSearchTerm >= 65 && intSearchTerm <= 90)
    {
        intSearchTerm -= 65;
    }
    return intSearchTerm;
}

int encryptPlaintext(int intPlaintext, string key)
{
    int ci_intPlaintext = caseInsensitive(intPlaintext);
    int ci_intCiphertext = key[ci_intPlaintext];
    return ci_intCiphertext;
}
