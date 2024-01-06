#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>
using namespace std;

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

class Handful
{
    private:
    int red;
    int green;
    int blue;

    void parse_cubes(string cubes) 
    {
        stringstream ss(cubes);
        int qty;
        string color;
        ss >> qty >> color;
        if(color.compare("blue") == 0) {
            blue = qty;
        } else if(color.compare("red") == 0) {
            red = qty;
        } else if(color.compare("green") == 0) {
            green = qty;
        }
    }

    public:
    Handful(string description)
    {
        red = 0;
        green = 0;
        blue = 0;

        string delim = ",";
        size_t pos = 0;
        string token;
        while((pos = description.find(delim)) != string::npos) {
            token = description.substr(0, pos);
            trim(token);
            //cout << token << endl;
            parse_cubes(token);
            description.erase(0, pos+delim.length());
            trim(description);
        }
        //cout << description << endl;
        parse_cubes(description);
    }

    bool is_handful_possible(int red, int green, int blue)
    {
        if(this->red <= red && this->green <= green && this->blue <= blue)
            return true;
        return false;
    }

    void update_power_handful(int &red, int &green, int &blue)
    {
        if(this->red > red) red = this->red;
        if(this->green > green) green = this->green;
        if(this->blue > blue) blue = this->blue;
    }

    void print_handful()
    {
        cout << "Red: " << this->red << " Green: " << this->green << " Blue: " << this->blue << endl;
    }
};

class Game
{
    private:
    int id;
    vector<Handful> handfuls;

    public:
    Game(string full_game)
    {
        size_t pos = 0;
        pos = full_game.find(":");
        //Skip over the "Game " part of the string
        string game_id_substr = full_game.substr(5, pos-5);
        stringstream game_id_ss(game_id_substr);
        game_id_ss >> id;
        //cout << "Game ID: " << id << endl;
        full_game.erase(0, pos+1);
        trim(full_game);
        //cout << full_game << endl;

        //Now get all of the handful strings parsed out
        string token;
        while((pos = full_game.find(";")) != string::npos) {
            token = full_game.substr(0, pos);
            trim(token);
            Handful hful = Handful(token);
            //hful.print_handful();
            handfuls.push_back(hful);
            full_game.erase(0, pos+1);
            trim(full_game);
        }

        Handful hful = Handful(full_game);
        //hful.print_handful();
        handfuls.push_back(hful);
    }

    // Evaluates whether the handfuls identified would be possible with a given number of blocks in the bag
    // Returns true if the game is possible, false if it is not
    bool is_game_possible(int red, int green, int blue)
    {
        for(int i = 0; i < handfuls.size(); i++) {
            if(handfuls[i].is_handful_possible(red, green, blue) == false)
                return false;
        }
        return true;
    }

    // Returns the cube "power" for this game.
    // The power is defined as the minimum number of each color cube required in the bag to make the game possible.
    // These three numbers are then multiplied together to get the power.
    int get_cube_power()
    {
        int red = 0, green = 0, blue = 0;
        for(int i = 0; i < handfuls.size(); i++) {
            handfuls[i].update_power_handful(red, green, blue);
        }
        return red * green * blue;
    }

    int get_id()
    {
        return id;
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
	vector<Game> games;

	myfile.open(argv[1]);
    
    while(!myfile.eof()) {
		getline(myfile, cur_line);

        Game g = Game(cur_line);

        games.push_back(g);
    }

    myfile.close();

    int p1_id_sum = 0;
    int power_sum = 0;
    for(int i = 0; i < games.size(); i++)
    {
        if(games[i].is_game_possible(12, 13, 14) == true) {
            p1_id_sum += games[i].get_id();
        }
        power_sum += games[i].get_cube_power();
    }

    cout << "Number of games: " << games.size() << endl;
    cout << "Part 1: " << p1_id_sum << endl;
    cout << "Part 2: " << power_sum << endl;
}