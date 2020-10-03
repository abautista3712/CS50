#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }

    // Limit input to be between 1 and 8
    while (n < 1 || n > 8);
    // Print Row
    for (int i = 0; i < n; i++)
    {
        // Print Left Column Spacer: "."
        for (int j = n - 1; j > i; j--)
        {
            printf(" ");
        }
        // Print Left Pyramid: "#"
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
            if (k == i)
            {
                printf("  ");
            }
        }
        // Print Right Pyramid: "#"
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}