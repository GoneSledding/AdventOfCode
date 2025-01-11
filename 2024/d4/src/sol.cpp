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

int find_all_xmas(vector<vector<char>> & puzzle)
{
    int p1_total = 0; 

    //Go through the data to find instances of XMAS going in any direction
    for(int row = 0; row < puzzle.size(); row++) {
        for(int col = 0; col < puzzle[row].size(); col++) {
            if(puzzle[row][col] == 'X') {
                //We found a starting point.
                //Search for a match going right
                if(col < (puzzle[row].size() - 3)) {
                    if(puzzle[row][col+1] == 'M' && puzzle[row][col+2] == 'A' && puzzle[row][col+3] == 'S')
                        p1_total++;
                }

                //Search for a match going left
                if(col >= 3) {
                    if(puzzle[row][col-1] == 'M' && puzzle[row][col-2] == 'A' && puzzle[row][col-3] == 'S')
                        p1_total++;
                }

                //Search for a match going up
                if(row >= 3) {
                    if(puzzle[row-1][col] == 'M' && puzzle[row-2][col] == 'A' && puzzle[row-3][col] == 'S')
                        p1_total++;
                }

                //Search for a match going down
                if(row < (puzzle.size() - 3)) {
                    if(puzzle[row+1][col] == 'M' && puzzle[row+2][col] == 'A' && puzzle[row+3][col] == 'S')
                        p1_total++;
                }

                //Search for a match going diagonal upper left
                if(row >= 3 && col >= 3) {
                    if(puzzle[row-1][col-1] == 'M' && puzzle[row-2][col-2] == 'A' && puzzle[row-3][col-3] == 'S')
                        p1_total++;
                }

                //Search for a match going diagonal upper right
                if(row >= 3 && col < (puzzle[row].size() - 3)) {
                    if(puzzle[row-1][col+1] == 'M' && puzzle[row-2][col+2] == 'A' && puzzle[row-3][col+3] == 'S')
                        p1_total++;
                }

                //Search for a match going diagonal lower left
                if(row < (puzzle.size() - 3) && col >= 3) {
                    if(puzzle[row+1][col-1] == 'M' && puzzle[row+2][col-2] == 'A' && puzzle[row+3][col-3] == 'S')
                        p1_total++;
                }

                //Search for a match going diagonal lower right
                if(row < (puzzle.size() - 3) && col < (puzzle[row].size() - 3)) {
                    if(puzzle[row+1][col+1] == 'M' && puzzle[row+2][col+2] == 'A' && puzzle[row+3][col+3] == 'S')
                        p1_total++;
                }
            }
        }
    }
    return p1_total;
}

int find_all_x_mas(vector<vector<char>> &puzzle)
{
    int total = 0;

    //Look for an 'A' in the center of the X to start.
    for(int row = 1; row < puzzle.size()-1; row++) {
        for(int col = 1; col < puzzle[row].size()-1; col++) {
            if(puzzle[row][col] == 'A') {
                //Search for 'M' in the upper and lower left followed by 'S' in the upper and lower right
                if(puzzle[row+1][col+1] == 'S' && puzzle[row-1][col+1] == 'S' && puzzle[row+1][col-1] == 'M' && puzzle[row-1][col-1] == 'M')
                    total++;

                //Search for 'M' in the upper and lower right followed by 'S' in the upper and lower left
                if(puzzle[row+1][col+1] == 'M' && puzzle[row-1][col+1] == 'M' && puzzle[row+1][col-1] == 'S' && puzzle[row-1][col-1] == 'S')
                    total++;

                //Search for 'M' in the upper right and left followed by 'S' in the lower right and left
                if(puzzle[row-1][col+1] == 'M' && puzzle[row-1][col-1] == 'M' && puzzle[row+1][col+1] == 'S' && puzzle[row+1][col-1] == 'S')
                    total++;

                //Search for 'S' in the upper right and left followed by 'M' in the lower right and left
                if(puzzle[row-1][col+1] == 'S' && puzzle[row-1][col-1] == 'S' && puzzle[row+1][col+1] == 'M' && puzzle[row+1][col-1] == 'M')
                    total++;
            }
        }
    }

    return total;
}

int main(int argc, char ** argv)
{
    if(argc < 2) {
		cout << "Not enough args" << endl;
		exit(1);
	}

	ifstream myfile;
    string cur_line;

    unsigned int p1_total = 0;
    unsigned int p2_total = 0;

    myfile.open(argv[1]);

    vector<vector<char>> puzzle;
    int row_id = 0;

    //Read in all of the input data to be processed
    while(!myfile.eof()) {
        vector<char> current_puzzle_line;
		getline(myfile, cur_line);
        istringstream ss(cur_line);
        char c;
        while(ss >> c) {
            if(c != '\n')
                current_puzzle_line.push_back(c);
        }
        puzzle.push_back(current_puzzle_line);
        //cout << "Length of row " << row_id << ": " << current_puzzle_line.size() << endl;
        row_id++;
    }

    myfile.close();

    //cout << "Number of rows: " << puzzle.size() << endl;

    p1_total = find_all_xmas(puzzle);
    cout << "part 1 answer: " << p1_total << endl;

    p2_total = find_all_x_mas(puzzle);
    cout << "part 2 answer: " << p2_total << endl;
}