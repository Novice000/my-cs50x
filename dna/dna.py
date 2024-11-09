import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print('dna.py [database.csv] [sequence.txt]')

    if sys.argv[1][-3] != 'csv' and len(sys.argv[1][-3]) > 3:
        print('database should be a csv file')

    if sys.argv[2][-3] != 'txt' and len(sys.argv[1][-3]) > 4:
        print('sequence not a text file')

    # TODO: Read database file into a variable
    dna_arr=[]
    dna_col=[]
    with open(sys.argv[1]) as data:
        reader=  csv.DictReader(data)
        dna_col= reader.fieldnames
        for row in reader:
            dna_arr.append(row)

    # holds column names excluding the name field
    dna_col = dna_col[1:]

    # TODO: Read DNA sequence file into a variable

    with open(sys.argv[2]) as seq:
        reader2= seq.read()

    # TODO: Find longest match of each STR in DNA sequence
    #adds the longest_match to a dictionary with the subsequence as the key
    match_dic = {}
    for i in dna_col:
        match_dic[i]= longest_match(reader2,i)

    # TODO: Check database for matching profiles
    #check for matches and prints the first name with all columns matched
    found_match= match_find(match_dic, dna_arr, dna_col)
    print(found_match)

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run

def match_find(dictionary_of_match, array_of_data_dic, dna_fields):
    match = ''
    NOM= 0
    for j  in range(len(array_of_data_dic)):
        for key in dictionary_of_match.keys():
            if dictionary_of_match[key] == int(array_of_data_dic[j][key]):
                match = array_of_data_dic[j]['name']
                NOM += 1
                if NOM == len(dna_fields):
                    return match
            else:
                match = 'No match'
                NOM = 0
                break

    return match
main()
