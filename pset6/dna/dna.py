import sys
import csv
import os

if len(sys.argv) != 3:
    print("Usage: python dna.py database.csv sequence.txt")
    exit(1)

database = sys.argv[1]
sequence = sys.argv[2]
dna_blocks = []
sequences = []
chel = {}

if os.path.exists(database):
    with open(database, 'r') as datafile:
        for index, row in enumerate(datafile):
            if index == 0:
                dna_blocks = [block for block in row.strip().split(',')][1:]
            else:
                current = row.strip().split(',')
                chel[current[0]] = [int(n) for n in current[1:]]
else:
    print("No such database or directory")
    exit(2)
if os.path.exists(sequence):
    file_argv2 = open(sequence, 'r').read()
    for block in dna_blocks:
        i = 0
        max_block = -1
        current_max = 0
        while i < len(file_argv2):
            cur_window = file_argv2[i:i + len(block)]
            if cur_window == block:
                current_max += 1
                max_block = max(max_block, current_max)
                i += len(block)
            else:
                current_max = 0
                i += 1
        sequences.append(max_block)
else:
    print("No such sequence or directory")
    exit(3)
for name, data in chel.items():
    if data == sequences:
        print(name)
        print(dna_blocks)
        print(sequences)
        print(chel)
        exit(0)
print("No match")
print(dna_blocks)
print(sequences)
print(chel)