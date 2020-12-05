from cs50 import get_int
from cs50 import get_string

while True:
    creditNum = get_int("Input CC number to see if valid: ")

    if creditNum > 0:
        counterDigits = countDigits(creditNum)

def countDigits(numberToCount):
    counterDigits = 0

    while numberToCount != 0:
        numberToCount = numberToCount / 10
        counterDigits += 1

    return counterDigits