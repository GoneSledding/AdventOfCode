#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int FindIndexOfUnsafeReport(vector<int> vec) 
{
    int i;

    bool increasing;

    if(vec[0] > vec[1]) increasing = false;
    else if(vec[0] < vec[1]) increasing = true;
    else if(vec[0] == vec[1]) return 0;

    for(i = 0; i < vec.size() - 1; i++) {
        if(increasing) {
            //Verify that the values are still increasing. Return if they aren't
            if(vec[i] >= vec[i+1])
                return i;
            //Verify that the values aren't increasing too fast
            if(vec[i] + 3 < vec[i+1])
                return i;
        } else {
            //Verify that the values are still decreasing. Return if they aren't
            if(vec[i] <= vec[i+1])
                return i;
            //Verify that the values aren't decreasing too quickly.
            if(vec[i] - 3 > vec[i+1])
                return i;
        }
    }
    return -1;
}

bool CheckForDampenedSafeReports(vector<int> vec) 
{
    vector<int> v1, v2, v3;
    int failed_index = FindIndexOfUnsafeReport(vec);
    if(failed_index == -1) return true;
    v1 = vec;
    v2 = vec;
    v3 = vec;
    v1.erase(v1.begin()+failed_index);
    if(FindIndexOfUnsafeReport(v1) == -1) return true;
    v2.erase(v2.begin()+failed_index+1);
    if(FindIndexOfUnsafeReport(v2) == -1) return true;
    if(failed_index > 0) {
        v3.erase(v3.begin()+failed_index-1);
        if(FindIndexOfUnsafeReport(v3) == -1) return true;
    }

    return false;
}

int main(int argc, char ** argv)
{
    if(argc < 2) {
		cout << "Not enough args" << endl;
		exit(1);
	}

	ifstream myfile;
	string cur_line;

    unsigned int p1_safe_reports = 0;
    unsigned int p2_safe_reports = 0;

    myfile.open(argv[1]);

    while(!myfile.eof()) {
        vector<int> levels;
		getline(myfile, cur_line);
        istringstream ss(cur_line);
        int n;
        while(ss >> n) {
            levels.push_back(n);
        }

        //cout << "Number of levels in report: " << levels.size() << endl;

        if(FindIndexOfUnsafeReport(levels) == -1) {
            p1_safe_reports++;
        }

        if(CheckForDampenedSafeReports(levels) == true) {
            p2_safe_reports++;
        }

    }

    myfile.close();

    cout << "P1 answer: " << p1_safe_reports << endl;
    cout << "P2 answer: " << p2_safe_reports << endl;
}