#include <fstream>
#include <iostream>

std::vector<std::string> extractFile(char* name){
    std::vector<std::string> stg;
    std::fstream stream(name, std::ios_base::in);

    if (stream.is_open()) {

        for(int i = 0; i < 1000; i++){
            std::string s;

            bool stayIn = true;

            while (stayIn){
                char c;

                stream.get(c);

                if(c == '\n'){
                    stayIn = false;
                }else{
                    s.push_back(c);
                }
            }

            stg.push_back(s);
        }

    }

    stream.close();
    return stg;
}

int decodeNumbersAndAddup(std::vector<std::string> v){
    int num = 0;

    std::unordered_map<std::string, int> checkMap;
    std::array<std::string, 10> checkList = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight","nine"};

    for(int i = 0; i < 10; i++){
        checkMap[checkList.at(i)] = i;
    }

    for(std::string x : v){

        char a = 0;

        int frontToBackIndex = 0;

        for(char y : x){
            if (isdigit(y)) {
                a = y;
                break;
            }else{

                for(std::string s : checkList){
                    bool really = true;
                    int stringLength = s.length();

                    for (int i = 0; i < stringLength; i++) {
                        if (frontToBackIndex+i > x.length()) {
                            really = false;
                            break;
                        }

                        if (x.at(frontToBackIndex+i)!=s.at(i)) {
                            really = false;
                            break;
                        }
                    }
                    if (really) {
                        a = std::to_string(checkMap[s]).front();
                        goto foundFrontToBackSilly;
                    }
                }

            }
            frontToBackIndex++;
        }

foundFrontToBackSilly:

        char b = 0;

        int backToFrontIndex = 0;

        std::reverse(x.begin(), x.end());

        for(char y : x ){
            if (isdigit(y)) {
                b = y;
                break;
            }else{

                for(std::string s : checkList){
                    bool really = true;
                    int stringLength = s.length();

                    std::string reversedString = s;
                    std::reverse(reversedString.begin(), reversedString.end());

                    for (int i = 0; i < stringLength; i++) {
                        if (backToFrontIndex+i > x.length()) {
                            really = false;
                            break;
                        }

                        if (x.at(backToFrontIndex+i)!=reversedString.at(i)) {
                            really = false;
                            break;
                        }
                    }
                    if (really) {
                        b = std::to_string(checkMap[s]).front();
                        goto foundBackToFrontSilly;
                    }
                }

            }
            backToFrontIndex++;
        }

foundBackToFrontSilly:

        std::string buf;
        buf.push_back(a);
        buf.push_back(b);

        num += std::stoi(buf);	
    }
    return num;
}

int main(){
    auto xf = extractFile((char*)"input.txt");
    std::cout << decodeNumbersAndAddup(xf) << '\n';

    return 0;
}
