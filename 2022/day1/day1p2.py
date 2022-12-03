#Written for python 3
#Written by Adam Klindworth
#Solves challenge for Advent of Code 2022 Day 1: Calorie Counting

import sys

elves = []
current_elf = 0
with open(sys.argv[1], 'r') as f:
    all_lines = f.readlines()

all_lines = [x.strip() for x in all_lines]

for line in all_lines:
    if(line == ''):
        #This is the end of this elf
        elves.append(current_elf)
        current_elf = 0
        continue

    current_elf += int(line)

elves.sort()
#print(elves)

print((elves[-1] + elves[-2] + elves[-3]))