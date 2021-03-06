from cs50 import get_float

numCoins = 0

while True:
    change = get_float("Input total change owed: ")

    if change > 0:
        cents = round(change * 100)

        # Handle quarters
        quarters = int(cents / 25)
        for i in range(quarters):
            numCoins += 1
            cents = cents - 25

        # Handle quarters
        dimes = int(cents / 10)
        for j in range(dimes):
            numCoins += 1
            cents = cents - 10

        # Handle nickels
        nickels = int(cents / 5)
        for k in range(nickels):
            numCoins += 1
            cents = cents - 5

        # Handle pennies
        numCoins = numCoins + cents

        print(f"{numCoins}")

        break