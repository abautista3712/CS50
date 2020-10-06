#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long creditNum;
    do
    {
        creditNum = get_long("Input CC number to see if valid: ");
    }

    while (creditNum <= 0);
    {
        // Check number of digits
        int countDigits = 0;
        long digitsNum = creditNum;
        while (digitsNum != 0)
        {
            digitsNum = digitsNum / 10;
            countDigits++;
        }
        if (countDigits == 13)
        {
            printf("VISA\n");
        }
        else if (countDigits == 15)
        {
            printf("AMEX\n");
        }
        else if (countDigits == 16)
        {
            printf("MASTERCARD or VISA\n");
        }
        printf("%i\n", countDigits);
    }
}