#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    int cents;
    int numCoins = 0;
    do
    {
        change = get_float("Input total change owed: ");
    }

    while (change <= 0);
    {
        cents = round(change * 100);
        int quarters = cents / 25;
        for (int i = 0; i < quarters; i++)
        {
            numCoins++;
        }
        printf("%i\n", numCoins);
    }
}