#include <stdio.h>
#include <cs50.h>
#include <math.h>

void luhnCheck(long ccNum, int countDigits);
void parseDigits(long numberToParse);

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
            luhnCheck(creditNum, countDigits);
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
                luhnCheck(creditNum, countDigits);
            }
            else
                (printf("MASTERCARD\n"));
        }
        // Any other combination of numbers are invalid
        else
        {
            printf("INVALID\n");
        }
    }
}

void luhnCheck(long ccNum, int countDigits)
{
    bool x = false;
    int checksum = 0;
    for (int i = 0; i < countDigits; i++)
    {
        if (x == true)
        {
            x = false;
            int digitValue = ccNum % 10;
            ccNum = ccNum / 10;
            printf("Digit Check: %i\n", digitValue);
            int doubleSum = digitValue * 2;
            printf("%i\n", doubleSum);
            if (doubleSum / 100 > 0)
            {
                checksum = checksum + doubleSum;
            }
            else
            {
                printf("There are two digits in doubleSum\n");
            }
            // printf("---CHECKSUM---\n%i\n", checksum);
        }
        else
        {
            x = true;
            int digitValue = ccNum % 10;
            ccNum = ccNum / 10;
        }
    }
}

// void parseDigits(long numberToParse)
// {
//     int digitValue = numberToParse % 10;
//     numberToParse = numberToParse / 10;
//     printf("%i\n", digitValue);
// }