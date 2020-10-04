#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float change;
    do
    {
        change = get_float("Input total change owed: ");
    } while (change <= 0);
    {
        int cents = change * 100;
        printf("%i\n", cents);
    }
}