#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>
#include <iterator>
#include <stdio.h>
#include <string.h>

using namespace std;

int multiply_sequences(string input)
{
    regex mul_regex("mul\\(\\d+,\\d+\\)");
    auto mul_begin = sregex_iterator(input.begin(), input.end(), mul_regex);
    auto mul_end = sregex_iterator();

    int sum = 0;

    cout << "Found " << distance(mul_begin, mul_end) << " instances of multiply in the input" << endl;

    for(sregex_iterator i = mul_begin; i != mul_end; i++) {
        smatch match = *i;
        string match_str = match.str();
        int num1, num2;
        sscanf(match_str.c_str(), "mul(%d,%d)", &num1, &num2);
        sum += num1*num2;
    }

    return sum;
}

int multiply_sequences_with_on_off(string input)
{
    regex mul_regex("(mul\\(\\d+,\\d+\\)|don't|do)");
    auto mul_begin = sregex_iterator(input.begin(), input.end(), mul_regex);
    auto mul_end = sregex_iterator();

    int sum = 0;
    bool should_multiply = true;

    cout << "Found " << distance(mul_begin, mul_end) << " instances of multiply or do or don't in the input" << endl;

    for(sregex_iterator i = mul_begin; i != mul_end; i++) {
        smatch match = *i;
        string match_str = match.str();
        if(match_str == "don't") {
            should_multiply = false;
            continue;
        } else if (match_str == "do") {
            should_multiply = true;
            continue;
        }

        if(should_multiply == true) {
            int num1, num2;
            sscanf(match_str.c_str(), "mul(%d,%d)", &num1, &num2);
            sum += num1*num2;
        }
    }

    return sum;
}

int main(int argc, char ** argv)
{
    if(argc < 2) {
		cout << "Not enough args" << endl;
		exit(1);
	}

	ifstream myfile;

    unsigned int p1_sum = 0;
    unsigned int p2_sum = 0;

    myfile.open(argv[1]);

    stringstream sstream;

    sstream << myfile.rdbuf();

    string str_input_data = sstream.str();

    cout << str_input_data << endl;

    p1_sum = multiply_sequences(str_input_data);
    p2_sum = multiply_sequences_with_on_off(str_input_data);

    cout << "part 1 answer: " << p1_sum << endl;
    cout << "part 2 answer: " << p2_sum << endl;

    myfile.close();

}