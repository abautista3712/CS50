#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int caseInsensitive(int intSearchTerm);
void handleCipher(string plaintext, string key);

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
    handleCipher(plaintext, key);
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

// int intKeyPosition (string key)
// {
//     for (int j = 0; j < 26; j++)
//     {
//         int keyPosition = (int) key[j]
//     }
// }

void handleCipher(string plaintext, string key)
{
    for (int j = 0, o = strlen(plaintext); j < o; j++)
    {
        int intPlaintext = (int)plaintext[j];
        intPlaintext = caseInsensitive(intPlaintext);
        printf("%i\n", intPlaintext);
    }
}
