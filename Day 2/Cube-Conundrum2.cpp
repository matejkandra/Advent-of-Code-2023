#include <array>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


std::vector<std::string> getGames(char* fileName){
    std::vector<std::string> gamesStrings;
    std::fstream stream(fileName, std::ios_base::in);

    if (stream.is_open()) {
        std::string s;

        while(std::getline(stream,s)){
            gamesStrings.push_back(s);
        }
    }

    stream.close();
    return gamesStrings;
}
int convertStringToInt(std::string s){
    int r{0};
    for (char c : s) {
        if (isdigit(c)) {
            r = r * 10 + (c - '0');
        }
    }
    return r;
}

void checkRGB(std::string* s, std::array<int, 3>* arr){
    if (s->find("red") != std::string::npos) {
        if (convertStringToInt(*s) > arr->at(0)) {
            arr->at(0) = convertStringToInt(*s);
        }
    }else if (s->find("green") != std::string::npos) {
        if (convertStringToInt(*s) > arr->at(1)) {
            arr->at(1) = convertStringToInt(*s);
        }

    }else if (s->find("blue") != std::string::npos) {
        if (convertStringToInt(*s) > arr->at(2)) {
            arr->at(2) = convertStringToInt(*s);
        }
    }else{
        throw std::invalid_argument("recieved invalid string");
    }
}

int main(){
    std::vector<std::string> gamesArr = getGames((char*)"input.txt");

    int total = 0;

    for (int i{0}; i < gamesArr.size(); i++) {

        size_t pos = gamesArr.at(i).find(':');
        int gameID{0};
        std::string gameIDString{gamesArr.at(i).substr(0, pos)};
        gamesArr.at(i) = gamesArr.at(i).substr(pos+1,gamesArr.at(i).length());

        gameID = convertStringToInt(gameIDString);

        std::cout << "GameID:"<< gameID << '\n';
        
        std::array<int, 3> RGBLOCAL = {0,0,0};
        
        while (gamesArr.at(i).find(';') != std::string::npos) {
            std::string subString1 = gamesArr.at(i).substr(0,gamesArr.at(i).find(';'));

            while (subString1.find(',') != std::string::npos) {
                std::string subString2 = subString1.substr(0,subString1.find(','));
                checkRGB(&subString2, &RGBLOCAL);
                subString1 = subString1.substr(subString1.find(',')+1,subString1.length());
            }

            checkRGB(&subString1, &RGBLOCAL);

            gamesArr.at(i) = gamesArr.at(i).substr(gamesArr.at(i).find(';')+1, gamesArr.at(i).length());
        }
        std::string subString1 = gamesArr.at(i);

        while (subString1.find(',') != std::string::npos) {
            std::string subString2 = subString1.substr(0,subString1.find(','));
            checkRGB(&subString2, &RGBLOCAL);
            subString1 = subString1.substr(subString1.find(',')+1,subString1.length());
        }
        checkRGB(&subString1, &RGBLOCAL);
        std::cout << RGBLOCAL.at(0)<<',' << RGBLOCAL.at(1)<<',' << RGBLOCAL.at(2) << '\n';
        total += RGBLOCAL.at(0) * RGBLOCAL.at(1) * RGBLOCAL.at(2);
    }

    std::cout << total << '\n';


    return 0;
}
