#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct position
{
    int row;
    int column;
    char lastMove;
    char direction1;
    char direction2;
};

position findS(vector<string> map){
    position pos;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].length(); j++)
        {
            if(map[i][j] == 'S'){
                pos.row = i;
                pos.column = j;
            }
        }
    }
    return pos;
}

void moveUpp(position& pos){
    pos.row = pos.row-1;
    pos.lastMove = 'U';
}
void moveDown(position& pos){
    pos.row = pos.row+1;
    pos.lastMove = 'D';
}
void moveLeft(position& pos){
    pos.column = pos.column-1;
    pos.lastMove = 'L';
}
void moveRight(position& pos){
    pos.column = pos.column+1;
    pos.lastMove = 'R';
}

void firstStep(vector<string>map, position& pos){
    if(map[pos.row+1][pos.column] == '|' || map[pos.row+1][pos.column] == 'J' || map[pos.row+1][pos.column] == 'L'){
        moveDown(pos);
    }
    else if(map[pos.row][pos.column-1] == '-' || map[pos.row][pos.column-1] == 'L' || map[pos.row][pos.column-1] == 'F'){
        moveLeft(pos);
    } 
    else if(map[pos.row][pos.column+1] == '-' || map[pos.row][pos.column+1] == '7' || map[pos.row][pos.column+1] == 'J'){
        moveRight(pos);
    }
    else if(map[pos.row-1][pos.column] == '|' || map[pos.row-1][pos.column] == '7' || map[pos.row-1][pos.column] == 'F'){
        moveUpp(pos);
    }

}

void settDirection(vector<string> map, position& pos){
    switch (map[pos.row][pos.column])
    {
    case '|':
        if(pos.lastMove == 'U'){
            pos.direction1 = 'L';
            pos.direction2 = 'L';
        }else{
            pos.direction1 = 'R';
            pos.direction2 = 'R';
        }
        break;
    case 'L':
        if(pos.lastMove == 'D'){
            pos.direction1 = 'R';
            pos.direction2 = 'U';
        }else{
            pos.direction1 = 'D';
            pos.direction2 = 'L';
        }
        break;
    case '-':
        if(pos.lastMove == 'R'){
            pos.direction1 = 'U';
            pos.direction2 = 'U';
        }else{
            pos.direction1 = 'D';
            pos.direction2 = 'D';
        }
        break;
    case 'J':
        if(pos.lastMove == 'R'){
            pos.direction1 = 'U';
            pos.direction2 = 'L';
        }else{
            pos.direction1 = 'R';
            pos.direction2 = 'D';
        }
        break;
    case '7':
        if(pos.lastMove == 'U'){
            pos.direction1 = 'D';
            pos.direction2 = 'L';
        }else{
            pos.direction1 = 'U';
            pos.direction2 = 'R';
        }
        break;    
    case 'F':
        if(pos.lastMove == 'U'){
            pos.direction1 = 'L';
            pos.direction2 = 'U';
        }else{
            pos.direction1 = 'D';
            pos.direction2 = 'R';
        }
        break;  
    default:
        break;
    }
}

void takeStep(vector<string> map, position& pos){
    pos.direction1 = ' ';
    pos.direction2 = ' ';
    switch (map[pos.row][pos.column])
    {
    case '|':
        if(pos.lastMove == 'U'){
            moveUpp(pos); 
            settDirection(map, pos);
        }else{
            moveDown(pos);
            settDirection(map, pos);
        }
        break;
    case 'L':
        if(pos.lastMove == 'D'){
            moveRight(pos); 
            settDirection(map, pos);
        }else{
            moveUpp(pos);
            settDirection(map, pos);
        }
        break;
    case '-':
        if(pos.lastMove == 'R'){
            moveRight(pos); 
            settDirection(map, pos);
        }else{
            moveLeft(pos);
            settDirection(map, pos);
        }
        break;
    case 'J':
        if(pos.lastMove == 'R'){
            moveUpp(pos); 
            settDirection(map, pos);
        }else{
            moveLeft(pos);
            settDirection(map, pos);
        }
        break;
    case '7':
        if(pos.lastMove == 'U'){
            moveLeft(pos); 
            settDirection(map, pos);
        }else{
            moveDown(pos);
            settDirection(map, pos);
        }
        break;    
    case 'F':
        if(pos.lastMove == 'U'){
            moveRight(pos); 
            settDirection(map, pos);
        }else{
            moveDown(pos);
            settDirection(map, pos);
        }
        break;  
    default:
        break;
    }
}

void checkNest(vector<string>& map, position pos){
    if(pos.direction1 == 'U' || pos.direction2 == 'U'){
        if(map[pos.row-1][pos.column] == '.'){
            map[pos.row-1][pos.column] = '#';
        }
    }
    if(pos.direction1 == 'D' || pos.direction2 == 'D'){
        if(map[pos.row+1][pos.column] == '.'){
            map[pos.row+1][pos.column] = '#';
        }
    }
    if(pos.direction1 == 'L' || pos.direction2 == 'L'){
        if(map[pos.row][pos.column-1] == '.'){
            map[pos.row][pos.column-1] = '#';
        }
    }
    if(pos.direction1 == 'R' || pos.direction2 == 'R'){
        if(map[pos.row][pos.column+1] == '.'){
            map[pos.row][pos.column+1] = '#';
        }
    }
}

int main(){
    fstream input("input.txt");
    ofstream out("out.txt");
    vector<string> pipeLines, writeMap;
    string in;
    int stepCounter = 0;

    char lastMove = ' ';
    while (!input.eof())
    {
        getline(input,in);
        pipeLines.push_back(in);
    }

    //createOutFile
    string tmp;
    for (int i = 0; i < in.length(); i++)
    {
        tmp += '.';
    }
    for (int i = 0; i < pipeLines.size(); i++)
    {
        writeMap.push_back(tmp);
    }
    
    //find S and do all moves. Write them on out
    position pos = findS(pipeLines);
    writeMap[pos.row][pos.column] = 'S';
    firstStep(pipeLines, pos);
    stepCounter++;
    
    while (pipeLines[pos.row][pos.column] != 'S')
    {
        writeMap[pos.row][pos.column] = pipeLines[pos.row][pos.column];
        takeStep(pipeLines,pos);
        stepCounter++;
    }
    cout << pos.row << " " << pos.column << "  " << pos.lastMove << " " << stepCounter << endl;
    cout << "half way is " << stepCounter/2 << endl;
    
    //Do all again but on the writeMap to find the nestPos
    pos = findS(pipeLines);
    firstStep(pipeLines, pos);

    //check for nests
    while (writeMap[pos.row][pos.column] != 'S')
    {  
        //cout << writeMap[pos.row][pos.column] <<"  "<< pos.direction1 << endl;
        takeStep(writeMap,pos);
        checkNest(writeMap,pos);
    }

    //add nests between empty room
    for (auto &&str : writeMap)
    {
        bool connected = false;
        int foundIndex = -1;
        for (int i = 0; i < str.length(); i++)
        {
            if(str[i] == '#' && foundIndex == -1){
                foundIndex = i;
            } 
            else if (foundIndex != -1 && str[i] == '#'){
                for (int j = foundIndex; j < i; j++)
                {
                    str[j] = '#';
                }
                
            } else if(foundIndex != -1 && str[i] != '.'){
                foundIndex = -1;
            }
            
        }
        
    }

    //count #s
    int totalnestplaces = 0;
    for (auto str : writeMap)
    {
        for (int i = 0; i < str.length(); i++)
        {
            if(str[i] == '#'){
                totalnestplaces++;
            }
        }
        
    }
    cout << totalnestplaces << endl;
    
    for (int i = 0; i < writeMap.size(); i++)
    {
        out << writeMap[i] << "\n";
    }
    out.close();
    input.close();
}