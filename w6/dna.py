import csv
from sys import argv, exit

if len(argv) != 3:
    print("Missing command-line argument")
    exit(1)

with open(f"./{argv[1]}") as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=",")
    line_count = 0
    for row in csv_reader:
        if line_count == 0:
            print(f'Columns Titles: {", ".join(row)}')
            line_count += 1
        else:
            print(f"Row {line_count}: ", end="")
            print(f'{", ".join(row)}')
            line_count += 1
    print(f"Processed {line_count} lines.")

with open(f"./{argv[2]}") as sequence_file:
    sequence_reader = csv.reader(sequence_file, delimiter=",")
    for row in sequence_reader:
        print(f'DNA Sequence: {", ".join(row)}')

exit(0)