#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char ** argv) {
    if(argc < 2) {
        std::cout << "Not enough args" << std::endl;
    }
    std::ifstream infile(argv[1]);
    std::string line;
    int currentPosition = 50;
    int instancesofLandingAtZero = 0;
    int instancesOfCrossingZero = 0;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            //std::cout << "Processing line: " << line << std::endl;
            char direction = line[0];
            int value = 0;
            try {
                value = std::stoi(line.substr(1));
            } catch (...) {
                std::cout << "Could not parse number in line: " << line << std::endl;
                continue;
            }

            if (direction == 'R') {
                currentPosition += value;
                //std::cout << "Moved right by " << value << ", position: " << currentPosition << std::endl;
            } else if (direction == 'L') {
                if(currentPosition == 0) {
                    //Don't count this one as crossing 0 as we're starting from 0
                    instancesOfCrossingZero--;
                }
                currentPosition -= value;
                //std::cout << "Moved left by " << value << ", position: " << currentPosition << std::endl;
            } else {
                std::cout << "Line starts with other: " << line << std::endl;
            }
            
            while(currentPosition < 0) {
                currentPosition += 100;
                // std::cout << "Crossed zero at position: " << currentPosition << " and value " << value << std::endl;
                instancesOfCrossingZero++;
            }
            while(currentPosition > 100) {
                currentPosition -= 100;
                // std::cout << "Crossed zero at position: " << currentPosition << " and value " << value << std::endl;
                instancesOfCrossingZero++;
            }
            currentPosition %= 100;
            // std::cout << "Current Position: " << currentPosition << std::endl;
            if(currentPosition == 0) {
                instancesofLandingAtZero++;
            }
        }
    }
    infile.close();
    std::cout << "Total instances of position 0: " << instancesofLandingAtZero << std::endl;
    std::cout << "Total instances of crossing 0: " << instancesOfCrossingZero << std::endl;
    std::cout << "Total crossing and landing at 0: " << (instancesofLandingAtZero + instancesOfCrossingZero) << std::endl;
    return 0;
}