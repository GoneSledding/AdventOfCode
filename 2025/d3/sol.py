import sys

def joltage_with_length(line, joltage_length):
    digits = [int(s) for s in line if s.isdigit()]
    max_num = 0
    
    current_start_index = 0
    for battery_number in range(joltage_length):
        maximum_digit = -1
        
        # There needs to be at least joltage_length digits left to form a number
        for i in range(current_start_index, len(digits) - joltage_length + 1 + battery_number):
            if maximum_digit < digits[i]:
                maximum_digit = digits[i]
                current_start_index = i + 1
        max_num = max_num * 10 + maximum_digit

    return max_num

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python sol.py <input_file>")
        sys.exit(1)
    total_p1_joltage = 0
    total_p2_joltage = 0
    with open(sys.argv[1], 'r') as f:
        for line in f:
            p1_result = joltage_with_length(line.strip(), 2)
            p2_result = joltage_with_length(line.strip(), 12)
            total_p1_joltage += p1_result
            total_p2_joltage += p2_result
            # print(f"Largest 2-digit number: {p1_result}")
            # print(f"Largest 12-digit number: {p2_result}")

    print(f"Total p1 joltage: {total_p1_joltage}")
    print(f"Total p2 joltage: {total_p2_joltage}")