#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main(int argc, char ** argv)
{
    if(argc < 2) {
		cout << "Not enough args" << endl;
		exit(1);
	}

	ifstream myfile;
	string cur_line;
	vector<int> Left;
	vector<int> Right;
	
	myfile.open(argv[1]);

    while(!myfile.eof()) {
		getline(myfile, cur_line);
		int l, r;
		istringstream ss(cur_line);
		ss >> l >> r;
        //cout << "Line: " << l << " " << r << endl;

		Left.push_back(l);
		Right.push_back(r);
    }

	myfile.close();

	sort(Left.begin(), Left.end());
	sort(Right.begin(), Right.end());
	unsigned int p1_ans = 0;

	for(int i = 0; i < Right.size(); i++) {
		p1_ans += abs(Left[i] - Right[i]);
	}

	unsigned int p2_ans = 0;
	for(int l : Left) {
		int mult = 0;
		for(int r : Right) {
			if(r == l) {
				mult++;
			}
		}
		p2_ans += l * mult;
	}

    cout << "Part 1 answer: " << p1_ans << endl;
	cout << "Part 2 answer: " << p2_ans << endl;
}