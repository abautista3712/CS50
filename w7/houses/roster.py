from cs50 import SQL
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

# Connect to DB
db = SQL("sqlite:///students.db")

db_info = db.execute("SELECT * FROM students")

print(f"{db_info}")