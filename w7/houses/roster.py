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
# Assign variable for length of db query
student_length = len(db_info)

for i in range(student_length):
    # Handle Special Case: Null value of middle name
    if db_info[i]['middle'] == None:
        db_info[i]['middle'] = " "
    else:
        db_info[i]['middle'] = " " + db_info[i]['middle'] + " "

    # Print data to console
    print(f"{db_info[i]['FIRST']}{db_info[i]['middle']}{db_info[i]['LAST']}, born {db_info[i]['birth']}")