from cs50 import get_int

while True:
    height = get_int("Height: ")

    if height >= 1 and height <= 8:
        for i in range(height):
            for j in range(height - 1, i, -1):
                print(".", end="")
            print("#", end="")
            print()

        break