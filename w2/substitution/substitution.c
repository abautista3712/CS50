#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

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
    printf("%s\n", plaintext);
}