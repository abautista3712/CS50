from cs50 import get_int

while True:
    height = get_int("Height: ")

    if height >= 1 and height <= 8:
        print(f"{height}")
        break