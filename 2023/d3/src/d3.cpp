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

/**
\brief Determine whether the character being sent in is a valid symbol.
\param c Character to check whether it is a symbol or not
\return true or false if it is a symbol or not.
**/
static bool issymbol(char c)
{
    if(c == '+' || c == '&' || c == '#' || c == '@' || c == '!' || c == '$' || c == '%' || c == '*' || c == '-' || c == '=' || c == '/')
        return true;
    return false;
}

class Symbol
{
    public:
    int x, y;
    bool is_special;
    Symbol(int new_x, int new_y)
    {
        this->x = new_x;
        this->y = new_y;
        this->is_special = false;
    }
};

class Part
{   
    public:
    int x, y, length;
    int part_number;
    Part()
    {

    }

    /**
     \brief Parses the part number from a string, updating the object with that information.
     \param x the current x coordinate in the schematic
     \param y the current y coordinate in the schematic
     \param str The string where the part number is. The first thing in the string should be the part number.
     \return The length of the part number found in the string.
    **/
    int parse_part_number(int x, int y, string str)
    {
        int pnum;
        stringstream ss(str);
        ss >> pnum;
        this->part_number = pnum;
        if(pnum >= 1000) this->length = 4;
        else if(pnum >= 100) this->length = 3;
        else if(pnum >= 10) this->length = 2;
        else if(pnum >= 0) this->length = 1;
        this->x = x;
        this->y = y;
        return this->length;
    }
};

class Schematic
{
    private:
    int num_rows;
    vector<Symbol> symbols;
    vector<Part> part_numbers;

    public:
    Schematic()
    {
        this->num_rows = 0;
    }

    /**
    \brief Adds a new line to the schematic
    \param str The entire line to be added to the schematic
    \return None
    **/
    void add_line(string str)
    {
        int row_position = 0;
        while(str.length() > 0) {
            //cout << str << endl;
            if(isdigit(str.c_str()[0])) {
                Part p = Part();
                int part_length = p.parse_part_number(row_position, this->num_rows, str);
                row_position += part_length;
                part_numbers.push_back(p);
                str.erase(0, part_length);
            } else if(str.c_str()[0] == '.') {
                str.erase(0, 1);
                row_position += 1;
            } else if(issymbol(str.c_str()[0]) == true) {
                Symbol s = Symbol(row_position, this->num_rows);
                if(str.c_str()[0] == '*') s.is_special = true;
                symbols.push_back(s);
                str.erase(0, 1);
                row_position += 1;
            }
        }
        
        this->num_rows++;
    }

    /**
    \brief Determines whether the part number is next to the symbol
    \param pnum Part number object
    \param sym Symbol
    \return Boolean determining whether the part number is valid or not.
    **/
    bool is_valid_part_number(Part pnum, Symbol sym)
    {
        if((pnum.x - 1) <= sym.x && (pnum.x + pnum.length) >= sym.x && (pnum.y - 1) <= sym.y && (pnum.y + 1) >= sym.y) {
            return true;
        }
        return false;
    }

    /**
    \brief Determines whether the '*' is part of a gear and calculates the gear ratio
    \param 
    \return Returns the gear ratio if it is. Zero if it isn't a gear.
    **/
    int calculate_gear_ratio(Symbol sym)
    {
        int gear_value = 0;
        for(int i = 0; i < part_numbers.size(); i++) {
            if(is_valid_part_number(part_numbers[i], sym) == true) {
                if(gear_value == 0) gear_value = part_numbers[i].part_number;
                else return gear_value * part_numbers[i].part_number;
            }
        }
        return 0;
    }

    /**
    \brief Calculates the sum of all gear ratios
    \return int, the sum of all gear ratios
    **/
    int calculate_gear_ratio_sum()
    {
        int sum = 0;
        for(int sym_ctr = 0; sym_ctr < symbols.size(); sym_ctr++) {
            if(symbols[sym_ctr].is_special == true) {
                sum += calculate_gear_ratio(symbols[sym_ctr]);
            }
        }
        return sum;
    }

    /**
    \brief Calculates the sum of the all of the valid part numbers.
    \return the sum of all of the part numbers
    **/
    int calculate_partnum_sum()
    {
        int sum = 0;
        // Go through all of the part numbers to determine if they are valid
        for(int i = 0; i < part_numbers.size(); i++) {
            //cout << "Part number " << part_numbers[i].part_number << " found" << endl;
            for(int sym_ctr = 0; sym_ctr < symbols.size(); sym_ctr++) {
                if(is_valid_part_number(part_numbers[i], symbols[sym_ctr]) == true) {
                    sum += part_numbers[i].part_number;
                    //cout << "Part number " << part_numbers[i].part_number << " is valid" << endl;
                    break;
                }
                /*if(sym_ctr +1 == symbols.size()) {
                    cout << "Part number " << part_numbers[i].part_number << " is not valid" << endl;
                }*/
            }
        }
        return sum;
    }

    void print_data()
    {
        cout << "Number of part numbers: " << part_numbers.size() << endl;
        cout << "Number of symbols: " << symbols.size() << endl;
        for(int i = 0; i < part_numbers.size(); i++) {
            cout << "Part number: " << part_numbers[i].part_number << " X: " << part_numbers[i].x << " Y: " << part_numbers[i].y << " Length: " << part_numbers[i].length << endl;
        }

        for(int i = 0; i < symbols.size(); i++) {
            cout << "Symbol X: " << symbols[i].x << " Y: " << symbols[i].y << endl;
        }
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
	Schematic engine;

	myfile.open(argv[1]);
    
    while(!myfile.eof()) {
		getline(myfile, cur_line);
        trim(cur_line);

        engine.add_line(cur_line);
    }

    myfile.close();

    //engine.print_data();
    int p1_sum = engine.calculate_partnum_sum();

    cout << "Part 1: " << p1_sum << endl;
    cout << "Part 2: " << engine.calculate_gear_ratio_sum() << endl;
}