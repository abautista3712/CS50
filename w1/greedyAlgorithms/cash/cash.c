#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        change = get_float("Input total change owed: ");
    }

    while (change <= 0);
    {
        int cents = round(change * 100);
        printf("%i\n", cents);
    }
}