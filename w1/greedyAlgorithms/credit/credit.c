#include <stdio.h>
#include <cs50.h>
#include <math.h>

int countDigits(long numberToCount);
void luhnCheck(long ccNum, int counterDigits);
// void parseDigits(long numberToParse);

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
            luhnCheck(creditNum, counterDigits);
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
            {
                (printf("MASTERCARD\n"));
                luhnCheck(creditNum, counterDigits);
            }
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
    int checkSum1 = 0;
    int checkSum2 = 0;
    int finalSum = 0;
    for (int i = 0; i < ccNumDigits; i++)
    {
        if (x == true)
        {
            x = false;
            // Read Digit Value
            int digitValue = ccNum % 10;
            ccNum = ccNum / 10;
            // printf("Digit Check: %i\n", digitValue);
            // Multiply Digit by 2
            int doubleSum = digitValue * 2;
            // printf("%i\n", doubleSum);
            int counterDigits = countDigits(doubleSum);
            // If product of digitValue has more than one digit, sum digits
            if (counterDigits < 2)
            {
                checkSum1 = checkSum1 + doubleSum;
            }
            else
            {
                for (int j = 0; j < counterDigits; j++)
                {
                    checkSum1 = checkSum1 + (doubleSum % 10);
                    doubleSum = doubleSum / 10;
                }
            }
            // printf("---checkSum1---\n%i\n", checkSum1);
        }
        else
        {
            x = true;
            // Read Digit Value
            int digitValue = ccNum % 10;
            ccNum = ccNum / 10;
            checkSum2 = checkSum2 + digitValue;
        }
    }
    finalSum = checkSum1 + checkSum2;
    // printf("finalSum = %i\n", finalSum);
    int digitValue = ccNum % 10;
    ccNum = ccNum / 10;
    // printf("%i\n",digitValue);
    if (digitValue != 0)
    {
        printf("INVALID\n");
    }
}