import csv
from sys import argv, exit

if len(argv) != 3:
    print("Missing command-line argument")
    exit(1)

# Open CSV file
with open(f"./{argv[1]}") as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=",")
    line_count = 0
    for csv_row in csv_reader:
        if line_count == 0:
            # Save STR and STR length into variables
            str = csv_row[1]
            str_length = len(str)

            print(str)

            # Open DNA Sequence txt file
            with open(f"./{argv[2]}") as sequence_file:
                dna = sequence_file.read()

                # Compare STR to DNA Sequence
                # Declare empty dictionary and max_consecutive variable
                str_match = {}
                max_consecutive = 0

                # Loop through every DNA base
                for i in range(len(dna)):
                    # Initialize default value of str_match[i] to 0
                    str_match[i] = 0

                    # Check STR against DNA sequence and count consecutive occurances
                    if dna[i:(len(str) + i)] == str:
                        if str_match[i - len(str)] > 0:
                            str_match[i] = str_match[i - len(str)] + 1
                        else:
                            str_match[i] = 1

                    # Keep track of max number of consecutive STR matches
                    if str_match[i] > max_consecutive:
                        max_consecutive = str_match[i]

                print(str_match)
                print(f"max_consecutive = {max_consecutive}")
            # for i in range(len(Full DNA Sequence)):
            #     if STR Segment == DNA Sequence Segment:
            #         STR Count += 1
            #         i += 1
            #     else:
            #         i += 1wha

            # print(f'Columns Titles: {", ".join(row)}')

                # for i in (len(row)):
                    # if row[i] == "AGATC":
                #         print("MATCH")
            line_count += 1
        else:
            print(f"Row {line_count}: ", end="")
            print(f'{", ".join(csv_row)}')
            line_count += 1
    print(f"Processed {line_count} lines.")


# for row in sequence_reader:
# with open(f"./{argv[2]}") as sequence_file:
#     print(sequence_file.read())
    # print(f'DNA Sequence: {", ".join(row)}')
    # print(f"{len(sequence_reader)}")

exit(0)