#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }

    while (n < 1);
    // Print Row = n
    for (int i = 0; i < n; i++)
    {
        // Print Column: "."
        for (int j = n; j > i; j--)
        {
            printf(" ");
        }
        // Print Column: "#"
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}