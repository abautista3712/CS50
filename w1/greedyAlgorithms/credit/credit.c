#include <stdio.h>
#include <cs50.h>
#include <math.h>

int countDigits(long numberToCount);
void luhnCheck(long ccNum, int counterDigits);
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
        int counterDigits = countDigits(creditNum);
        // Cards with 13 digits are VISA
        if (counterDigits == 13)
        {
            printf("VISA\n");
            luhnCheck(creditNum, counterDigits);
        }
        // Cards with 15 digits are VISA
        else if (counterDigits == 15)
        {
            printf("AMEX\n");
        }
        // Cards with 16 digits are either VISA or Mastercard
        else if (counterDigits == 16)
        {
            // Cards starting with 4 as the first digit are VISA
            if (floor(creditNum / (1 * pow(10, 15))) == 4)
            {
                printf("VISA\n");
                luhnCheck(creditNum, counterDigits);
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

int countDigits(long numberToCount)
{
    int counterDigits = 0;
    while (numberToCount != 0)
    {
        numberToCount = numberToCount / 10;
        counterDigits++;
    }
    return counterDigits;
}

void luhnCheck(long ccNum, int ccNumDigits)
{
    bool x = false;
    int checksum = 0;
    for (int i = 0; i < ccNumDigits; i++)
    {
        if (x == true)
        {
            x = false;
            int digitValue = ccNum % 10;
            ccNum = ccNum / 10;
            printf("Digit Check: %i\n", digitValue);
            int doubleSum = digitValue * 2;
            printf("%i\n", doubleSum);
            int counterDigits = countDigits(doubleSum);
            if (counterDigits < 2)
            {
                checksum = checksum + doubleSum;
            }
            else
            {
                for (int j = 0; j < counterDigits; j++)
                {
                    checksum = checksum + (doubleSum % 10);
                    doubleSum = doubleSum / 10;
                }
            }
            printf("---CHECKSUM---\n%i\n", checksum);
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