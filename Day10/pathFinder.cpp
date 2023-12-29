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

void takeStep(vector<string> map, position& pos){
    switch (map[pos.row][pos.column])
    {
    case '|':
        if(pos.lastMove == 'U'){
            moveUpp(pos); 
        }else{
            moveDown(pos);
        }
        break;
    case 'L':
        if(pos.lastMove == 'D'){
            moveRight(pos); 
        }else{
            moveUpp(pos);
        }
        break;
    case '-':
        if(pos.lastMove == 'R'){
            moveRight(pos); 
        }else{
            moveLeft(pos);
        }
        break;
    case 'J':
        if(pos.lastMove == 'R'){
            moveUpp(pos); 
        }else{
            moveLeft(pos);
        }
        break;
    case '7':
        if(pos.lastMove == 'U'){
            moveLeft(pos); 
        }else{
            moveDown(pos);
        }
        break;    
    case 'F':
        if(pos.lastMove == 'U'){
            moveRight(pos); 
        }else{
            moveDown(pos);
        }
        break;  
    default:
        break;
    }
}

int main(){
    fstream input("input.txt");
    vector<string> pipeLines;
    string in;
    char lastMove = ' ';
    while (!input.eof())
    {
        getline(input,in);
        pipeLines.push_back(in);
    }

    //find S
    position pos = findS(pipeLines);

    //L-|JF7
    //check connections with s
    //4 sides to check
    //upp, down, left, right
    if(pipeLines[pos.row-1][pos.column] == '|' || pipeLines[pos.row-1][pos.column] == '7' || pipeLines[pos.row-1][pos.column] == 'F'){
        moveUpp(pos);
    }
    else if(pipeLines[pos.row+1][pos.column] == '|' || pipeLines[pos.row+1][pos.column] == 'J' || pipeLines[pos.row+1][pos.column] == 'L'){
        moveDown(pos);
    }
    else if(pipeLines[pos.row][pos.column-1] == '-' || pipeLines[pos.row][pos.column-1] == 'L' || pipeLines[pos.row][pos.column-1] == 'F'){
        moveLeft(pos);
    } 
    else if(pipeLines[pos.row][pos.column+1] == '-' || pipeLines[pos.row][pos.column+1] == '7' || pipeLines[pos.row][pos.column+1] == 'J'){
        moveRight(pos);
    } 

    cout << pos.row << " " << pos.column << "  " << pos.lastMove << endl;
    
    //take a step
    int stepCounter = 1;
    while (pipeLines[pos.row][pos.column] != 'S')
    {
        takeStep(pipeLines,pos);
        stepCounter++;
    }
    cout << pos.row << " " << pos.column << "  " << pos.lastMove << " " << stepCounter << endl;
    cout << "half way is " << stepCounter/2;
    
}