#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Set variables 'change', 'cents', and 'numCoins'
    float change;
    int cents;
    int numCoins = 0;

    // Ask for user input
    do
    {
        change = get_float("Input total change owed: ");
    }

    // Continue to ask for user input until number is > 0
    while (change <= 0);
    {
        // Convert dollars to cents by multiplying change by 100 and round number using math.h library
        cents = round(change * 100);
        // Handle quarters: divide cents by 25. Each loop will add 1 to numCoins and subtract 25 from cents to produce balance.
        int quarters = cents / 25;
        for (int i = 0; i < quarters; i++)
        {
            numCoins++;
            cents = cents - 25;
        }
        // Handle dimes: divide remaining cents by 10. Each loop will add 1 to numCoins and subtract 10 to produce balance.
        int dimes = cents / 10;
        for (int j = 0; j < dimes; j++)
        {
            numCoins++;
            cents = cents - 10;
        }
        // Handle nickels: divide remaining cents by 5. Each loop will add 1 to numCoins and subtract 5 to produce balance.
        int nickels = cents / 5;
        for (int k = 0; k < nickels; k++)
        {
            numCoins++;
            cents = cents - 5;
        }
        // Handle pennies: remaining cents are added to numCoins.
        numCoins = numCoins + cents;
        printf("%i\n", numCoins);
    }
}