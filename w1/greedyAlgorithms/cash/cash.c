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
            cents = cents - 25;
            numCoins++;
        }
        int dimes = cents / 10;
        for (int j = 0; j < dimes; j++)
        {
            cents = cents - 10;
            numCoins++;
        }
        int nickels = cents / 5;
        for (int k = 0; k < nickels; k++)
        {
            cents = cents - 5;
            numCoins++;
        }
        numCoins = numCoins + cents;
        printf("%i\n", numCoins);
    }
}