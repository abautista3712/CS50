from cs50 import SQL
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

# Connect to DB
db = SQL("sqlite:///students.db")

# Assign data from db to variables
db_name = db.execute(f"SELECT first, middle, last FROM students WHERE house = '{argv[1]}' ORDER BY last, first ASC")
db_birth = db.execute(f"SELECT birth FROM students WHERE house = '{argv[1]}'")

# Handle pringting to console
# Assign variable for length of db query
student_length = len(db_name)

for i in range(student_length):
    # Handle Special Case: Null value of middle name
    if db_name[i]['middle'] == None:
        db_name[i]['middle'] = " "
    else:
        db_name[i]['middle'] = " " + db_name[i]['middle'] + " "

    # Print data to console
    print(f"{db_name[i]['FIRST']}{db_name[i]['middle']}{db_name[i]['LAST']}, born {db_birth[i]['birth']}")