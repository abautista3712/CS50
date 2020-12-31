from cs50 import SQL
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

# Connect to DB
db = SQL("sqlite:///students.db")

# Assign data from db to variables
db_info = db.execute(f"SELECT first, middle, last, birth FROM students WHERE house = '{argv[1]}' ORDER BY last, first ASC")

# Handle pringting to console
for i in db_info:
    first, middle, last, birth = i['first'], i['middle'], i['last'], i['birth']
    print(f"{first} {middle + ' ' if middle else ''}{last}, born {birth}")