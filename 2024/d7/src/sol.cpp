#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <stdint.h>

bool recursiveAddMul(const std::vector<uint64_t>& vec, uint64_t test, size_t idx = 0, uint64_t currentValue = 0) {
    if (idx == vec.size()) {
        //std::cout << "Current Value: " << currentValue << std::endl;
        return currentValue == test;
    }
    // Try addition
    if (recursiveAddMul(vec, test, idx + 1, currentValue + vec[idx])) return true;
    // Try multiplication
    if (recursiveAddMul(vec, test, idx + 1, currentValue * vec[idx])) return true;
    return false;
}

bool recursivePart2(const std::vector<uint64_t>& vec, uint64_t test, size_t idx = 0, uint64_t currentValue = 0) {
    if (idx == vec.size()) {
        //std::cout << "Current Value: " << currentValue << std::endl;
        return currentValue == test;
    }
    // Try addition
    if (recursivePart2(vec, test, idx + 1, currentValue + vec[idx])) return true;
    // Try multiplication
    if (recursivePart2(vec, test, idx + 1, currentValue * vec[idx])) return true;
    // Try Concatenation
    std::string current_str = std::to_string(currentValue) + std::to_string(vec[idx]);
    uint64_t new_value = std::stoull(current_str);
    if (recursivePart2(vec, test, idx + 1, new_value)) return true;
    return false;
}

int main(int argc, char ** argv) 
{

    if(argc < 2) {
		std::cout << "Not enough args" << std::endl;
		exit(1);
	}

    // Your code here
    std::ifstream infile;
    uint64_t p1_total = 0;
    uint64_t p2_total = 0;
    infile.open(argv[1]);
    std::string line;
    while (std::getline(infile, line)) {
        // Process the line
        std::vector<uint64_t> current_puzzle_line;
        std::istringstream ss(line);
        
        uint64_t test_value;
        ss >> test_value;
        //Using this rather than reading the : into a variable since I'm not going to use it.
        ss.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    
        //std::cout << "First value: " << test_value << std::endl;
        int values;
        while(ss >> values) {
            //std::cout << values << std::endl;
            current_puzzle_line.push_back(values);
        }
        
        //std::cout << line << std::endl;

        p1_total += recursiveAddMul(current_puzzle_line, test_value, 1, current_puzzle_line[0]) ? test_value : 0;
        p2_total += recursivePart2(current_puzzle_line, test_value, 1, current_puzzle_line[0]) ? test_value : 0;
    }
    infile.close();

    std::cout << "Part 1 total: " << p1_total << std::endl;
    std::cout << "Part 2 total: " << p2_total << std::endl;
    
    return 0;
}