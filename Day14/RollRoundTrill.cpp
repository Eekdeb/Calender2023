#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
void getMap(fstream& input, vector<string>& map);
void transform(vector<string> input, vector<string>& output);
void rollLeft(vector<string> &map);

void getMap(fstream& input, vector<string>& map){
    string buff;
    map.clear();
    while (input.peek() != '\n' && !input.eof())
    {
        getline(input,buff);
        map.push_back(buff);
        //cout << buff << endl;
    }
    getline(input,buff);
}

void transform(vector<string> input, vector<string>& output){
    output.clear();
    for (int i = 0; i < input[0].length(); i++)
    {
        output.push_back("");
        for (int j = 0; j < input.size(); j++)
        {
            output[i] += input[j][i];
        }
    }
}

void rollLeft(vector<string> &map){
    int moveCount;
    for (int m = 0; m < map.size(); m++)    
    {
        moveCount = 0;
        for (int i = 0; i < map[m].length(); i++)
        {
            if(map[m][i] == '.') moveCount++;
            if(map[m][i] == '#') moveCount = 0;
            if(map[m][i] == 'O'){
                map[m][i] = '.';
                map[m][i-moveCount] = 'O';
            } 
        }
    }
}

void rollRight(vector<string> &map){
    int moveCount;
    for (int m = 0; m < map.size(); m++)    
    {
        moveCount = 0;
        for (int i = map[m].length(); i >= 0; i--)
        {
            if(map[m][i] == '.') moveCount++;
            if(map[m][i] == '#') moveCount = 0;
            if(map[m][i] == 'O'){
                map[m][i] = '.';
                map[m][i+moveCount] = 'O';
            } 
        }
        
    }
}

void rollUpp(vector<string> &map){
    int moveCount;
    for (int i = 0; i < map[0].length(); i++)
    {
        moveCount = 0;
        for (int j = 0; j < map.size(); j++)
        {
            //rad(string) column
            if(map[j][i] == '.') moveCount++;
            if(map[j][i] == '#') moveCount = 0;
            if(map[j][i] == 'O'){
                map[j][i] = '.';
                map[j-moveCount][i] = 'O';
            }
        }
        
    }
}

void rollDown(vector<string> &map){
    int moveCount;
    for (int i = 0; i < map[0].length(); i++)
    {
        moveCount = 0;
        for (int j = map.size()-1; j >= 0; j--)
        {
            //rad(string) column
            if(map[j][i] == '.') moveCount++;
            if(map[j][i] == '#') moveCount = 0;
            if(map[j][i] == 'O'){
                map[j][i] = '.';
                map[j+moveCount][i] = 'O';
            }
        }
        
    }
}

void rollRound(vector<string> &map){
    rollUpp(map);
    rollLeft(map);
    rollDown(map); 
    rollRight(map);
}

bool compareMaps(vector<string> map1, vector<string> map2){
    if(map1.size() == map2.size()){
        for (int i = map1.size()-1; i >= 0; i--)
        {
            if(map1[i].compare(map2[i])) {
                //cout << "Heeeeeeeeeeeeeeeeeeer " << i << endl;
                return false;
            }
            
        }
    }else return false;

    if(map1 != map2) return false;
    return true;
}

int getPoints(vector<string> map){
    int points;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if(map[i][j] == 'O'){
                points += map.size()-i;
            }
        }
    }
    return points;
}

int getLoopSize(vector<string> map, int startIndex, int maxLoopSize){
    vector<string> mapCopy;
    //go until a loop hopefully exists
    for(int i = 0; i < startIndex; i++){
        rollRound(map);
    }
    mapCopy = map;
    int count;
    for (count = 0; count < maxLoopSize; count++)
    {
        rollRound(map);
        if(compareMaps(map,mapCopy)) break;
    }
    //+1 becous starting at 0
    return count+1;
}

int getLoopStart(vector<string> map, int loopSize, int maxValue){
    int iteration = 0;
    std::map<int,vector<string>> saved;
    saved[iteration] = map;
    
    //init one loopsize
    for(int i = 0; i < loopSize; i++){
        iteration++;
        rollRound(map);
        }
    saved[iteration] = map;
    if(compareMaps(saved[iteration], saved[0])) return 0;
    
    //find first time map loops
    while (!compareMaps(saved[iteration], saved[iteration-loopSize]) && iteration < maxValue)
    {
        for(int i = 0; i < loopSize; i++){
            iteration++;
            rollRound(map);
        }
        saved[iteration] = map;
    }

    //save data from this loop to compare with maps before
    iteration = iteration-loopSize;
    map = saved[iteration];
    for(int i = 0; i < loopSize; i++){
        iteration++;
        rollRound(map);
        saved[iteration] = map;
    }
    
    //go back 2 iterations and see what the earliest iteration is start
    iteration = iteration-2*loopSize;
    map = saved[iteration];
    while (!compareMaps(map,saved[iteration+loopSize]))
    {
        iteration++;
        rollRound(map);
        saved[iteration] = map;
    }
    //
    return iteration-1;
}

int leastNrOfRounds(int endNr, int loopSize, int startLoop){
    return ((endNr-startLoop)%loopSize)+startLoop;
}

int main(){
    fstream input("input.txt");
    //My input is looping every 44 steps beginning at 94 moves
    //(1 000 000 000-93)%44 = 27
    //93+27=120

    //TODO automatically find the loop time and where it starts
    //take (endNr-startLoop)%loopTime = iteration in loop ends up at endNr
    //get to that iteration and calc points
    vector<string> map,map1;
    int loopSize, startLoop, leastLoop;
    getMap(input,map);
    loopSize = getLoopSize(map,300,200);
    startLoop = getLoopStart(map,loopSize,500);
    leastLoop = leastNrOfRounds(1000000000,loopSize,startLoop);
    
    for (int i = 0; i < leastLoop; i++)
    {
        rollRound(map);
    }

    int points = getPoints(map);
    cout << points << endl;
    input.close();
    return 0;
}