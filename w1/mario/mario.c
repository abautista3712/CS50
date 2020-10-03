#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    } while (n < 1);
    // Print Row = n
    for (int i = 0; i < n; i++)
    {
        // Print Column = (i + 1)
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}