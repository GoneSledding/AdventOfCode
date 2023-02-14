#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

class CrateStacks
{
    private:
        vector<string> initial_state;
        vector<vector<char>> stacks;

        void add_to_stacks(int stack_num, char id)
        {
            this->stacks[stack_num].push_back(id);
        }

    public:
        CrateStacks(void)
        {
            
        }

        void append_initial_state(string line)
        {
            //cout << line << endl;
            this->initial_state.push_back(line);
        }

        void parse_initial_state()
        {
            //set up the correct number of vectors in the stacks vector based on the length of the final string
            int num_stacks = this->initial_state.back().length() / 4;
            //cout << "Number of stacks: " << num_stacks << endl;
            for(int i = 0; i < num_stacks; i++) {
                this->stacks.push_back(vector<char>());
            }

            //We're going to go from the bottom up to get things in the right order
            for(int i = this->initial_state.size()-1; i >= 0; i--) {
                //cout << this->initial_state[i] << endl;
                for(int n = 1; n < this->initial_state[i].length(); n+=4) {
                    char c = this->initial_state[i][n];
                    //cout << "Parsing: " << c << endl;
                    if(c != ' ') {
                        this->add_to_stacks(n/4, c);
                    }
                }
            }
        }

        //This method moves cargo from one stack to another one by one
        void rearrange_stacks_one_by_one(string rearrangement)
        {
            //cout << rearrangement << endl;
            vector<string> v = split(rearrangement, ' ');
            int qty = stoi(v[1]);
            int from = stoi(v[3]);
            int to = stoi(v[5]);

            for(int i = 0; i < qty; i++) {
                char tmp = this->stacks[from-1].back();
                this->stacks[from-1].pop_back();
                this->stacks[to-1].push_back(tmp);
            }
        }

        //This method moves cargo from one stack to another all at one time
        void rearrange_stacks_all_at_once(string rearrangement)
        {
            vector<char> tmp;
            vector<string> v = split(rearrangement, ' ');
            int qty = stoi(v[1]);
            int from = stoi(v[3]);
            int to = stoi(v[5]);

            for(int i = 0; i < qty; i++) {
                tmp.push_back(this->stacks[from-1].back());
                this->stacks[from-1].pop_back();
            }

            for(int i = 0; i < qty; i++) {
                this->stacks[to-1].push_back(tmp.back());
                tmp.pop_back();
            }
            
        }

        void print_current_state()
        {
            for(auto stack : stacks) {
                for(auto c : stack) {
                    cout << c << " ";
                }
                cout << endl;
            }
        }

        void print_top_of_stacks()
        {
            for(auto stack : stacks) {
                cout << stack.back();
            }
            cout << endl;
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

    CrateStacks * stacks_norm = new CrateStacks();
    CrateStacks * stacks_at_once = new CrateStacks();

    //First loop is to get the number of stacks and initial state
    while(!myfile.eof()) {
        getline(myfile, cur_line);

        if(cur_line.find("[") != string::npos) {
            stacks_norm->append_initial_state(cur_line);
            stacks_at_once->append_initial_state(cur_line);
        }

        if(cur_line.length() == 1)
            break;
    }

    //Now that we have the lines stored, do the actual parsing of our initial state
    stacks_norm->parse_initial_state();
    stacks_at_once->parse_initial_state();
    //stacks->print_current_state();

    //Now get all the moves to be made and process them
    while(!myfile.eof()) {
        getline(myfile, cur_line);
        
        //The length value is arbitrary here, we're just trying to avoid lines with just newlines on it
        if(cur_line.length() > 3)
        {
            stacks_norm->rearrange_stacks_one_by_one(cur_line);
            stacks_at_once->rearrange_stacks_all_at_once(cur_line);
        }
    }

    stacks_norm->print_top_of_stacks();
    stacks_at_once->print_top_of_stacks();

    return 0;
}