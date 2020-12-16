import cs50
import csv
from sys import argv, exit

if len(argv) != 3:
    print("Missing command-line argument")
    exit(1)

# Create database
open(f"students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")

# # Open CSV file
# with open(f"./{argv[1]}") as csv_file:
#     csv_reader = csv.reader(csv_file, delimiter=",")