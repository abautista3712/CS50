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
        if line_count == 0:
            line_count += 1
        else:
            # Split first/middle/last name by spaces
            name_split = csv_row[0].split()

            print(f"{name_split}")
            if len(name_split) == 2:
                print("name_split == 2")
                first = name_split[0]
                middle = None
                last = name_split[1]
            if len(name_split) == 3:
                print("name_split == 3")
                first = name_split[0]
                middle = name_split[1]
                last = name_split[2]

            print(f"{len(name_split)}")

            db.execute("INSERT INTO students (id, first, middle, last) VALUES(?, ?, ?, ?)", line_count, first, middle, last)

            db.execute("SELECT * FROM students")

        print(f"Line count: {line_count}")
        line_count += 1

