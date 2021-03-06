#include <stdio.h>
#include <cs50.h>
#include <math.h>

int countDigits(long numberToCount);
bool luhnCheck(long ccNum, int counterDigits);
void verifyCC(long ccNum, int counterDigits);

int main(void)
{
    long creditNum;
    // Ask for input until satisfies 'while' condition
    do
    {
        creditNum = get_long("Input CC number to see if valid: ");
    }

    while (creditNum <= 0);
    {
        // Check number of digits
        int counterDigits = countDigits(creditNum);
        // Cards with 13, 15, 16 digits are VALID and will undergo further verification
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

// Function to count credit card digits
int countDigits(long numberToCount)
{
    // Set counter to 0
    int counterDigits = 0;
    // While credit card has more than one digit to check, run the loop
    while (numberToCount != 0)
    {
        // Each loop divides the credit card number by 10 and adds 1 to the counter
        numberToCount = numberToCount / 10;
        counterDigits++;
    }
    return counterDigits;
}

void verifyCC(long ccNum, int ccNumDigits)
{
    if (luhnCheck(ccNum, ccNumDigits) == false)
    {
        printf("INVALID\n");
    }
    else
    {
        // AMEX Verification: First Two Numbers
        int firstTwoCheck = floor(ccNum / (1 * pow(10, ccNumDigits - 2)));
        if (firstTwoCheck == 34 | firstTwoCheck == 37)
        {
            printf("AMEX\n");
        }
        // MASTERCARD Verification: First Two Numbers
        else if (firstTwoCheck == 51 | firstTwoCheck == 52 | firstTwoCheck == 53 | firstTwoCheck == 54 | firstTwoCheck == 55)
        {
            printf("MASTERCARD\n");
        }
        // VISA: First Number
        else if (floor(ccNum / (1 * pow(10, ccNumDigits - 1))) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

// CheckSum Algorithm
bool luhnCheck(long ccNum, int ccNumDigits)
{
    bool x = false;
    int checkSum1 = 0;
    int checkSum2 = 0;
    int finalSum = 0;
    for (int i = 0; i < ccNumDigits; i++)
    {
        // Calulate checkSum1
        if (x == true)
        {
            x = false;
            // Read Digit Value
            int digitValue = ccNum % 10;
            // printf("checkSum1 %i\n", checkSum1);
            // printf("checkSum1 digitValue %i\n", digitValue);
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
        // Calculate checkSum2
        else
        {
            x = true;
            // Read Digit Value
            int digitValue = ccNum % 10;
            ccNum = ccNum / 10;
            checkSum2 = checkSum2 + digitValue;
        }
    }
    // finalSum Check
    finalSum = checkSum1 + checkSum2;
    int digitValue = finalSum % 10;
    finalSum = finalSum / 10;
    if (digitValue == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}