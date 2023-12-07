#include <algorithm>
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


bool doesHaveAdjacentSymbol(int i, int j, std::vector<std::string> inputArr, std::array<int, 2>* resPtr){

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
            inputArr.at(i+yx.at(0)).at(j+yx.at(1)) == '*') {
            *resPtr = yx;
            return true;
        }
    }
    return false;

}

int main(){
    std::vector<std::string> input = loadFilesLines();

    int total{0};
    std::vector<std::array<int, 2>> nums;
    std::vector<int> numLoc;

    for (int i{0}; i < input.size(); i++) {
        for (int j {0}; j < input.at(i).length() ; j++) {
            bool isAdjacent = false;
            int a = 0;
            std::array<int, 2> resSym{0};

            if (isdigit(input.at(i).at(j))) {
                while ((j + a) != input.at(i).length() && isdigit(input.at(i).at(j + a))) {
                    if (doesHaveAdjacentSymbol(i, j+a, input,&resSym)) {
                        isAdjacent = true;
                        resSym = {resSym.at(0)+i, resSym.at(1)+j+a};
                    }

                    a++;
                }
            }
            if(isAdjacent){
                nums.push_back(resSym);
                numLoc.push_back(std::stoi(input.at(i).substr(j,a)));
            }
            j += a;
        }
    }

    int i = 0;
    for (std::array<int, 2> x: nums) {
        std::cout << x.front() << " , " << x.back()<< " : " << numLoc.at(i)  << '\n';
        i++;
    }

    if (numLoc.size() == nums.size()) {
        std::cout << "They are the same!" << '\n';
    }

    for (int i{0}; i < nums.size(); i++) {
        for (int j{0}; j < nums.size(); j++) {
            if (nums.at(i)  == nums.at(j) && i != j) {
                total += numLoc.at(i) * numLoc.at(j);
                numLoc.at(i) = 0;
                numLoc.at(j) = 0;
            }
        }
    }

    std::cout << total << '\n';
    return 0;
}
