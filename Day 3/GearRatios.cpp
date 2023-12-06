#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> loadFilesLines(){
    std::vector<std::string> v;
    std::fstream fs("input");
    
    if (!fs.is_open()) {
        throw std::errc::no_such_file_or_directory;
    }
    
    std::string s;

    while (std::getline(fs, s)) {
        v.push_back(s);
    }

    return v;
}


bool doesHaveAdjacentSymbol(int i, int j, std::vector<std::string> inputArr){

    std::array<std::array<int, 2>, 8> mappings;
    mappings.at(0) = {-1,-1};
    mappings.at(1) = {-1,0};
    mappings.at(2) = {-1,1};
    mappings.at(3) = {0,1};
    mappings.at(4) = {1,1};
    mappings.at(5) = {1,0};
    mappings.at(6) = {1,-1};
    mappings.at(7) = {0,-1};
    
    for (std::array<int, 2> yx : mappings) {
        if (i+yx.at(0) > 0 && i+yx.at(0) < inputArr.size()  &&
            j+yx.at(1) > 0 && j+yx.at(1) < inputArr.at(i+yx.at(0)).length() &&
            !isdigit(inputArr.at(i+yx.at(0)).at(j+yx.at(1))) &&
            inputArr.at(i+yx.at(0)).at(j+yx.at(1)) != '.') {
            return true;
        }
    }
    return false;

}

int main(){
    std::vector<std::string> input = loadFilesLines();

    int total{0};

    for (int i{0}; i < input.size(); i++) {
        for (int j {0}; j < input.at(i).length() ; j++) {
            bool isAdjacent = false;
            int a = 0;

            if (isdigit(input.at(i).at(j))) {
                while ((j + a) != input.at(i).length() && isdigit(input.at(i).at(j + a))) {
                    if (doesHaveAdjacentSymbol(i, j+a, input)) {
                        isAdjacent = true;
                    }
                    a++;
                }
            }
            if(isAdjacent){
                total += std::stoi(input.at(i).substr(j,a));
            }
            j += a;
        }
    }
    std::cout << total << '\n';
    return 0;
}
