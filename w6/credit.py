from cs50 import get_int
from cs50 import get_string
from math import floor

def main():
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
            break

# Function to count credit card digits
def countDigits(numberToCount):
    counterDigits = 0

    while numberToCount != 0:
        numberToCount = numberToCount // 10
        counterDigits += 1

    return counterDigits

# Function to verify CC and print which type of card
def verifyCC(ccNum, ccNumDigits):
    if luhnCheck(ccNum, ccNumDigits) == False:
        print("INVALID")
    else:
        firstTwoCheck = int(str(ccNum)[:2])

        # AMEX Verification via First Two Numbers
        if firstTwoCheck == 34 or firstTwoCheck == 37:
            print("AMEX")

        # MASTERCARD Verification via First Two Numbers
        elif firstTwoCheck == 51 or firstTwoCheck == 52 or firstTwoCheck == 54 or firstTwoCheck == 55:
            print("MASTERCARD")

        # VISA via First Number
        elif int(str(ccNum)[:1]) == 4:
            print("VISA")

        else:
            print("INVALID")

# CheckSum Algorithm
def luhnCheck(ccNum, ccNumDigits):
    x = False
    checkSum1 = 0
    checkSum2 = 0
    finalSum = 0

    for i in range(ccNumDigits):
        # Calculate checkSum1
        if x == True:
            x = False
            digitValue = ccNum % 10
            ccNum = ccNum / 10
            doubleSum = digitValue * 2
            counterDigits = countDigits(doubleSum)
            if counterDigits < 2:
                checkSum1 = checkSum1 + doubleSum
            else:
                for j in range(counterDigits):
                    checkSum1 = checkSum1 + (doubleSum % 10)
                    doubleSum = doubleSum / 10

        # Calculate checkSum2
        else:
            x = True
            digitValue = ccNum % 10
            ccNum = ccNum / 10
            checkSum2 = checkSum2 + digitValue

    # finalSum Check
    finalSum = checkSum1 + checkSum2
    digitValue = finalSum % 10
    finalSum = finalSum / 10
    if digitValue == 0:
        return True
    else:
        return False

main()