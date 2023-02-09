#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

class SectionPair
{
    private:
        int rng_one_lower;
        int rng_one_higher;
        int rng_two_lower;
        int rng_two_higher;
        string full_line;

    public:
        SectionPair(string input)
        {
            this->full_line = input;
            size_t one_high_loc = input.find("-");
            size_t two_low_loc = input.find(",");
            size_t two_high_loc = input.find("-", two_low_loc);
            this->rng_one_lower = stoi(input, NULL, 10);
            this->rng_one_higher = stoi(input.substr(one_high_loc+1, input.size() - one_high_loc), NULL, 10);
            this->rng_two_lower = stoi(input.substr(two_low_loc+1, input.size() - two_low_loc), NULL, 10);
            this->rng_two_higher = stoi(input.substr(two_high_loc+1, input.size() - two_high_loc), NULL, 10);
        }

        void print_range() 
        {
            cout << "Range 1: " << this->rng_one_lower << "-" << this->rng_one_higher << endl;
            cout << "Range 2: " << this->rng_two_lower << "-" << this->rng_two_higher << endl;
        }

        bool is_fully_contained()
        {
            if ((this->rng_one_lower <= this->rng_two_lower && this->rng_one_higher >= this->rng_two_higher) || (this->rng_two_lower <= this->rng_one_lower && this->rng_two_higher >= this->rng_one_higher))
            {
                return true;
            }
            return false;
        }
        
        bool is_overlapping()
        {
            if ((this->rng_one_lower <= this->rng_two_higher && this->rng_one_higher >= this->rng_two_lower) || (this->rng_two_lower <= this->rng_one_higher && this->rng_two_higher >= this->rng_one_lower))
            {
                return true;
            }
            return false;
        }
};

int main(int argc, char ** argv)
{
    if(argc < 2) {
        cout << "Not enough args" << endl;
        exit(1);
    }

    ifstream myfile;
    string cur_line;
	
    myfile.open(argv[1]);

    int part1_score = 0;
    int part2_score = 0;
    while(!myfile.eof()) {
        getline(myfile, cur_line);
        SectionPair cur_pair = SectionPair(cur_line);
        part1_score += cur_pair.is_fully_contained() ? 1 : 0;
        //cur_pair.print_range();
        part2_score += cur_pair.is_overlapping() ? 1 : 0;
    }

    cout << part1_score << endl;
    cout << part2_score << endl;

    return 0;
}