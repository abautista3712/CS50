#include <stdio.h>
#include <cs50.h>
#include <math.h>

void test(void);

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
        // Cards with 13 digits are VISA
        if (countDigits == 13)
        {
            printf("VISA\n");
        }
        // Cards with 15 digits are VISA
        else if (countDigits == 15)
        {
            printf("AMEX\n");
        }
        // Cards with 16 digits are either VISA or Mastercard
        else if (countDigits == 16)
        {
            // Cards starting with 4 as the first digit are VISA
            if (floor(creditNum / (1 * pow(10, 15))) == 4)
            {
                printf("VISA\n");
            }
            else
                (printf("MASTERCARD\n"));
        }
        // Any other combination of numbers are invalid
        else
        {
            printf("INVALID\n");
        }
        printf("%i\n", countDigits);
        test();
    }
}

void test(void)
{
    printf("test\n");
}