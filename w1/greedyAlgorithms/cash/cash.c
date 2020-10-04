#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float n;
    do
    {
        n = get_float("Input total change owed: ");
    } while (n < 1);
    {
        printf("%.2f\n", n);
    }
}