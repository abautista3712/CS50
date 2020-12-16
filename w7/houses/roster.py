from cs50 import SQL
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

# Connect to DB
db = SQL("sqlite:///students.db")

# Assign data from db to variables
db_first = db.execute("SELECT first FROM students")
db_middle = db.execute("SELECT middle FROM students")
db_last = db.execute("SELECT last FROM students")
db_birth = db.execute("SELECT birth FROM students")

# Print to console
student_length = len(db.execute("SELECT * FROM students"))

for i in range(student_length):
    print(f"{db_first[i]['FIRST']} {db_middle[i]['middle']} {db_last[i]['LAST']}, born {db_birth[i]['birth']}")