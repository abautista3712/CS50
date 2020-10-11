#include <stdio.h>
#include <cs50.h>
#include <math.h>

int countDigits(long numberToCount);
void verifyCC(long ccNum, int counterDigits);
void luhnCheck(long ccNum, int counterDigits);

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
        // Cards with 13, 15, 16 digits are VALID
        if (counterDigits == 13 | counterDigits == 15 | counterDigits == 16)
        {
            verifyCC(creditNum, counterDigits);
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

void verifyCC(long ccNum, int ccNumDigits)
{
    // AmEx Check First Two Numbers
    int firstTwoCheck = floor(ccNum / (1 * pow(10, ccNumDigits - 2)));
    if (firstTwoCheck == 34 | firstTwoCheck == 37)
    {
        luhnCheck(ccNum, ccNumDigits);
        printf("AMEX\n");
    }
    //  MasterCard Check First Two Numbers
    else if (firstTwoCheck == 51 | firstTwoCheck == 52 | firstTwoCheck == 53 | firstTwoCheck == 54 | firstTwoCheck == 55)
    {
        luhnCheck(ccNum, ccNumDigits);
        printf("MASTERCARD\n");
    }
    else if (floor(ccNum / (1 * pow(10, ccNumDigits - 1))) == 4)
    {
        luhnCheck(ccNum, ccNumDigits);
        printf("VISA\n");
    }
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
            // Multiply Digit by 2
            int doubleSum = digitValue * 2;
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
    int digitValue = ccNum % 10;
    ccNum = ccNum / 10;
    if (digitValue != 0)
    {
        printf("INVALID\n");
    }
}