#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

//Class represents one round of Rock Paper Scissors played
class RockPaperScissors {
    private:
    char opp;
    char usr;

    public:
    RockPaperScissors(string input) {
        this->opp = input[0];
        this->usr = input[2];
    }

    RockPaperScissors (char opp, char usr) {
        this->opp = opp;
        this->usr = usr;
    }

    friend bool operator==(const RockPaperScissors &lhs, const RockPaperScissors &rhs)
    {
        if(lhs.opp == rhs.opp && lhs.usr == rhs.usr)
            return true;
        return false;
    }

    int calculate_score()
    {
        int score = 0;
        if(*this == RockPaperScissors('A', 'X')) score += 4;
        else if(*this == RockPaperScissors('A', 'Y')) score += 8;
        else if(*this == RockPaperScissors('A', 'Z')) score += 3;
        else if(*this == RockPaperScissors('B', 'X')) score += 1;
        else if(*this == RockPaperScissors('B', 'Y')) score += 5;
        else if(*this == RockPaperScissors('B', 'Z')) score += 9;
        else if(*this == RockPaperScissors('C', 'X')) score += 7;
        else if(*this == RockPaperScissors('C', 'Y')) score += 2;
        else if(*this == RockPaperScissors('C', 'Z')) score += 6;

        return score;
    }

    void implement_strategy()
    {
        if(*this == RockPaperScissors('A', 'X')) this->usr = 'Z';
        else if(*this == RockPaperScissors('A', 'Y')) this->usr = 'X';
        else if(*this == RockPaperScissors('A', 'Z')) this->usr = 'Y';
        else if(*this == RockPaperScissors('B', 'X')) this->usr = 'X';
        else if(*this == RockPaperScissors('B', 'Y')) this->usr = 'Y';
        else if(*this == RockPaperScissors('B', 'Z')) this->usr = 'Z';
        else if(*this == RockPaperScissors('C', 'X')) this->usr = 'Y';
        else if(*this == RockPaperScissors('C', 'Y')) this->usr = 'Z';
        else if(*this == RockPaperScissors('C', 'Z')) this->usr = 'X';
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
        RockPaperScissors p = RockPaperScissors(cur_line);
        part1_score += p.calculate_score();
        p.implement_strategy();
        part2_score += p.calculate_score();
    }

    cout << part1_score << endl;
    cout << part2_score << endl;

    return 0;
}