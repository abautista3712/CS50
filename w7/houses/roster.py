from cs50 import SQL
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

# Connect to DB
db = SQL("sqlite:///students.db")

# Assign data from db to variables
db_name = db.execute("SELECT first, middle, last FROM students ORDER BY last, first ASC")
db_birth = db.execute("SELECT birth FROM students")

# Print to console
student_length = len(db.execute("SELECT * FROM students"))

for i in range(student_length):
    print(f"{db_name[i]['FIRST']} {db_name[i]['middle']} {db_name[i]['LAST']}, born {db_birth[i]['birth']}")