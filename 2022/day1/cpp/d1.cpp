#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
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
	vector<int> elves;
	
	myfile.open(argv[1]);

	int current_elf = 0;
	while(!myfile.eof()) {
		getline(myfile, cur_line);
		//cout << cur_line.length() << endl;
		if(cur_line.length() == 1) {
			elves.push_back(current_elf);
			current_elf = 0;
			continue;
		}
		current_elf += stoi(cur_line);
	}
	elves.push_back(current_elf);

	sort(elves.begin(), elves.end());

	//for(auto elf : elves) {
	//	cout << elf << endl;
	//}

	int num_elves = elves.size();

	cout << "Largest number of calories: " << elves[num_elves-1] << endl;
	cout << "Highest three combined: " << elves[num_elves-1] + elves[num_elves-2] + elves[num_elves-3] << endl;

	return 0;
}