import cs50
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

# Create database
open(f"students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")

# Create tables
db.execute("CREATE TABLE students (id INT, first TEXT, middle TEXT, last TEXT, PRIMARY KEY(id))")

# Open CSV file
with open(f"{argv[1]}", "r") as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=",")

    # Variable to count lines
    line_count = 0

    for csv_row in csv_reader:
        print(f"{csv_row[0]}")
        print(f"{line_count}")
        line_count += 1
