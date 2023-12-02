#include <vector>
#include <fstream>
#include <iostream>


struct Round{
    int red = 0;
    int green = 0;
    int blue = 0;
};

struct Game{
    int id;
    std::vector<Round>;
};

int getNumberOfLinesInAFile(char* fileName){
    int lines = 0;
	std::fstream stream(fileName, std::ios_base::in);
	
	if (stream.is_open()) {
        while(!stream.eof()){

            char c;
            stream.get(c);
            if (c == '\n') {
                lines++;
            }
        }
	}

	stream.close();
	return lines - 1;
}

std::vector<Game> loadGameData(char* name){
    std::vector<Game> games;
	std::fstream stream(name, std::ios_base::in);
	
	if (stream.is_open()) {
        int totalLines = getNumberOfLinesInAFile((char*)"input.txt");

        for (int gamesIterator; gamesIterator < totalLines; gamesIterator++) {
            
        }
	}

	stream.close();
	return games;
}

int main(){
    std::vector<Game> games = loadGameData((char*)"input.txt");

    return 0;
}