#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

class Rucksack
{
    private:
        string compartment_one;
        string compartment_two;
        string compartments;
        string priorities = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        int get_priority(char c) {
            return this->priorities.find(c)+1;
        }

    public:
        Rucksack(string compartments)
        {
            this->compartments = compartments;
            this->compartment_one = compartments.substr(0, compartments.length()/2);
            this->compartment_two = compartments.substr(compartments.length()/2, compartments.length()/2);
        }

        int calc_duplicates()
        {
            int pri_score = 0;
            for (char c : this->compartment_one) {
                if(this->compartment_two.find(c) != string::npos) {
                    pri_score += this->get_priority(c);
                    break;
                }
            }
            return pri_score;
        }

        int find_badge(Rucksack obj2, Rucksack obj3)
        {
            for(char c : this->compartments) {
                if(obj2.compartments.find(c) != string::npos && obj3.compartments.find(c) != string::npos) {
                    return this->get_priority(c);
                }
            }
            return 0;
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
        Rucksack current_ruck1 = Rucksack(cur_line);
        part1_score += current_ruck1.calc_duplicates();

        getline(myfile, cur_line);
        Rucksack current_ruck2 = Rucksack(cur_line);
        part1_score += current_ruck2.calc_duplicates();

        getline(myfile, cur_line);
        Rucksack current_ruck3 = Rucksack(cur_line);
        part1_score += current_ruck3.calc_duplicates();

        part2_score += current_ruck1.find_badge(current_ruck2, current_ruck3);
    }

    cout << part1_score << endl;
    cout << part2_score << endl;

    return 0;
}