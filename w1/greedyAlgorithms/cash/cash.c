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
        if (cents >= 25)
        {
            int quarters = cents / 25;
            if (cents % 25 == 0)
            {
                numCoins = quarters;
            }
            else
            {
                cents = cents - 25 * quarters;
                numCoins = cents;
            }
        }
        printf("%i\n", numCoins);
    }
}