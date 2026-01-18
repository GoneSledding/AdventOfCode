import sys

if len(sys.argv) < 2:
	print("Usage: python solve.py <input_file>")
	sys.exit(1)


with open(sys.argv[1], 'r') as file:
	groups_of_numbers = [line.strip().split() for line in file.readlines()]

#print(groups_of_numbers)

total_sum_p1 = 0

operations = groups_of_numbers[-1]
del groups_of_numbers[-1]
#print(groups_of_numbers)
#print(operations)

while(len(operations) > 0):
	current_operation = operations.pop(0)
	op_total = int(groups_of_numbers[0].pop(0))
	for i in range(1, len(groups_of_numbers)):
		next_number = int(groups_of_numbers[i].pop(0))
		if current_operation == '+':
			op_total += next_number
		elif current_operation == '*':
			op_total *= next_number
	total_sum_p1 += op_total

print("Part 1:", total_sum_p1)

# Part 2 is truly brand new, so we're just going to entirely start over
with open(sys.argv[1], 'r') as file:
	raw_lines = [line.rstrip('\n') for line in file.readlines()]

total_sum_p2 = 0
operations = raw_lines[-1].split()
del raw_lines[-1]
number_of_columns = len(operations)
#print(f"Number of columns: {number_of_columns}")
groups_of_numbers = []

#We need to preserve the location of the spaces in the given input, because it actually matters
#We also know that the length of each column within each line is not guaranteed to be consistent
for col in range(number_of_columns):
	#Find the length of the current column
	column_length = 0
	all_blank = False
	while(all_blank == False):
		all_blank = True
		for line in raw_lines:
			if(len(line) > column_length and line[column_length] != ' '):
				all_blank = False
		if(all_blank == False):
			column_length += 1
	#print(f"Column Length: {column_length}")
	#Now pull that column from each line
	column = [l[0:column_length] for l in raw_lines]
	groups_of_numbers.append(column)
	#print(column)
	#Now remove that column from each line
	raw_lines = [''.join(l[column_length+1:]) for l in raw_lines]

#Go through each of the columns
for column_id in range(len(groups_of_numbers)):
	current_column = groups_of_numbers[column_id]

	#Get the longest length of the numbers
	current_length = len(current_column[0])
	
	created_numbers = []
	while(current_length > 0):
		created_number = ''
		for number in current_column:
			created_number += number[current_length - 1]
		#print(f"Created number: {created_number}")
		created_numbers.append(int(created_number.strip()))
		current_length -= 1

	#Now that we have our new numbers, do the operation with them
	current_operation = operations.pop(0)
	op_total = created_numbers.pop(0)
	for i in range(len(created_numbers)):
		next_number = created_numbers.pop(0)
		if current_operation == '+':
			op_total += next_number
		elif current_operation == '*':
			op_total *= next_number
	#print(f"Column {column_id} total: {op_total}")
	total_sum_p2 += op_total
print("Part 2:", total_sum_p2)