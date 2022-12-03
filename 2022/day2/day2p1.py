#Written for python 3
#Written by Adam Klindworth
#Solves challenge for Advent of Code 2022 Day 2: Rock Paper Scissors

with open('input.txt', 'r') as f:
    all_lines = f.readlines()

all_lines = [x.strip() for x in all_lines]

for line in all_lines:
    