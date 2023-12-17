#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
using namespace std;

int main(int argc, char ** argv)
{

    if(argc < 2) {
		cout << "Not enough args" << endl;
		exit(1);
	}

	ifstream myfile;
	string cur_line;
	
	myfile.open(argv[1]);

    int p1_calibration_sum = 0;
    int p2_calibration_sum = 0;

    array<std::string, 9> tokens{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	while(!myfile.eof()) {
		getline(myfile, cur_line);
		//cout << cur_line.length() << endl;
		int first_found = cur_line.find_first_of("0123456789");
        int last_found = cur_line.find_last_of("0123456789");
        if(!(first_found == std::string::npos && last_found == std::string::npos)) {
            string str_p1_calibration_value = string(1, cur_line[first_found]) + cur_line[last_found];
            //cout << str_p1_calibration_value << endl;
            p1_calibration_sum += stoi(str_p1_calibration_value);
        } else { first_found = 99; last_found = -1; }

        int p2_first_token_id;
        int p2_last_token_id;
        int p2_best_last_pos = -1;
        int p2_best_first_pos = 99;

        //Find the first position where a word version of a digit is found
        for(int i = 0, max = tokens.size(); i < max; ++i) {
            int const found_pos = cur_line.find(tokens[i]);
            if(found_pos == std::string::npos) { continue; }
            if(found_pos >= p2_best_first_pos) { continue; }

            p2_best_first_pos = found_pos;
            p2_first_token_id = i;
        }

        //Find the last position where a word version of a digit is found
        for(int i = 0, max = tokens.size(); i < max; ++i) {
            int const found_pos = cur_line.rfind(tokens[i]);
            if(found_pos == std::string::npos) { continue; }
            if(found_pos <= p2_best_last_pos) { continue; }

            p2_best_last_pos = found_pos;
            p2_last_token_id = i;
        }
        
        //Now determine the calibration value, whether it was an actual digit or a word version
        int p2_first_found = (first_found < p2_best_first_pos) ? cur_line[first_found]-0x30 : p2_first_token_id+1;
        int p2_last_found = (last_found > p2_best_last_pos) ? cur_line[last_found]-0x30 : p2_last_token_id+1;
        p2_calibration_sum += (p2_first_found*10) + p2_last_found;
	}

    cout << p1_calibration_sum << endl;
    cout << p2_calibration_sum << endl;

    myfile.close();

    return 0;
}