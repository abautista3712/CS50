from cs50 import get_int
from cs50 import get_string
from math import floor

while True:
    creditNum = get_int("Input CC number to see if valid: ")

    if creditNum > 0:
        # Check number of digits
        counterDigits = countDigits(creditNum)
        # Cards with 13, 15, 16 digits are VALID and will undergo further verification
        if counterDigits == 13 or counterDigits == 15 or counterDigits == 16:
            verifyCC(creditNum, counterDigits)
        # Any other combination of numbers are invalid
        else:
            print("INVALID")

# Function to count credit card digits
def countDigits(numberToCount):
    counterDigits = 0

    while numberToCount != 0:
        numberToCount = numberToCount / 10
        counterDigits += 1

    return counterDigits

# Function to verify CC and print which type of card
def verifyCC(ccNum, ccNumDigits):
    if luhnCheck(ccNum, ccNumDigits) == false:
        print("INVALID")
    else:
        firstTwoCheck = floor(ccNum / 1 * (10 ** ccNumDigits - 2))

        # AMEX Verification via First Two Numbers
        if firstTwoCheck == 34 or firstTwoCheck == 37:
            print("AMEX")

        # MASTERCARD Verification via First Two Numbers
        elif firstTwoCheck == 51 or firstTwoCheck == 52 or firstTwoCheck == 54 or firstTwoCheck == 55:
            print("MASTERCARD")

        # VISA via First Number
        elif floor(ccNum / (1 * (10 ** ccNumDigits - 1))) == 4:
            print("VISA")

        else:
            print("INVALID")