import csv
from sys import argv, exit

if len(argv) != 3:
    print("Missing command-line argument")
    exit(1)

# Open CSV file
with open(f"./{argv[1]}") as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=",")

    # Declare empty dictionaries to handle comparison between STR max match and DNA db
    dna_db = {}
    str_max_match = {}

    # Variable to count lines
    line_count = 0

    for csv_row in csv_reader:
        if line_count == 0:
            # Save STR and STR length into variables
            for i in range(1, len(csv_row)):
                str = csv_row[i]
                str_length = len(str)

                # print(str)

                # Open DNA Sequence txt file
                with open(f"./{argv[2]}") as sequence_file:
                    dna = sequence_file.read()

                    # Compare STR to DNA Sequence
                    # Declare empty dictionary and max_consecutive_match variable
                    str_match = {}
                    max_consecutive_match = 0

                    # Loop through every DNA base
                    for j in range(len(dna)):
                        # Initialize default value of str_match[j] to 0
                        str_match[j] = 0

                        # Check STR against DNA sequence and count consecutive occurances
                        if dna[j:(len(str) + j)] == str:
                            if j >= len(str) and str_match[j - len(str)] > 0:
                                str_match[j] = str_match[j - len(str)] + 1
                            else:
                                str_match[j] = 1

                        # Keep track of max number of consecutive STR matches
                        if str_match[j] > max_consecutive_match:
                            max_consecutive_match = str_match[j]

                    # Insert max consecutive STR matches into str_max_match dictionary
                    str_max_match[f"STR{i}"] = max_consecutive_match

            line_count += 1
        else:
            # Insert data into DNA db dictionary
            for i in range(len(csv_row)):
                if i == 0:
                    dna_db["Name"] = csv_row[i]
                    dna_db["max_match_ratio"] = 0
                else:
                    dna_db[f"STR{i}"] = int(csv_row[i])

            # Compare STRs with DNA database and log matches in max_match_ratio
            for j in range(1, len(csv_row)):
                if str_max_match[f"STR{j}"] == dna_db[f"STR{j}"]:
                    dna_db["max_match_ratio"] += 1

                # Calculations during last loop
                if j == len(csv_row) - 1:
                    # If max_match_ratio == 1, print name and exit
                    if (dna_db["max_match_ratio"] / (len(csv_row) - 1)) == 1:
                        print(dna_db["Name"])
                        exit(0)
                    # Else calculate and assign max_match_ratio for further analysis
                    else:
                        dna_db["max_match_ratio"] = (dna_db["max_match_ratio"] / (len(csv_row) - 1))

            # print(dna_db)
            # print(str_max_match)

    # print(f"Processed {line_count} lines.")

print("No match")
exit(0)