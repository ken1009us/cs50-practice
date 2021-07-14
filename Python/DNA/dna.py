import csv
import sys


def main():
    if len(sys.argv) == 3:
        name = data_process()
        print(name)

    else:
        print("Usage: python dna.py data.csv sequence.txt")


def data_process():
    # Open csv file and convert to dictionary to store the data
    with open(sys.argv[1], "r") as csv_file:
        data = csv.DictReader(csv_file)
        dna_dict_list = list(data)

    # Open text file
    with open(f"{sys.argv[2]}", "r") as sq:
        sys.argv[2] = csv.reader(sq)
        for content in sys.argv[2]:
            str_sq = content[0]

    max_count = []
    # For each STR, counts the time of consecutive repeats
    for i in range(1, len(data.fieldnames)):
        max_count.append(0)
        str_type = data.fieldnames[i]
        for j in range(len(str_sq)):
            count = 0
            length = len(str_type)
            # conditional, if STR matches with string in the text file
            if str_sq[j:(j+length)] == str_type:
                k = 0
                # consecutive repeats
                while str_sq[(j+k):(j+k+length)] == str_type:
                    count += 1
                    k += length

                if count > max_count[i-1]:
                    max_count[i-1] = count

    # Compare data
    # For each row of dictionary
    for p in range(len(dna_dict_list)):
        match = 0
        # For each STR
        for m in range(1, len(data.fieldnames)):
            if int(dna_dict_list[p][data.fieldnames[m]]) == max_count[m - 1]:
                match += 1

            # Print the name if they are matched
            if match == (len(data.fieldnames) - 1):
                return dna_dict_list[p]['name']

    return 'No match'


if __name__ == "__main__":
    main()
