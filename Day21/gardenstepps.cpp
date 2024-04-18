#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

struct position
{
    int row;
    int col;
};
inline bool operator<(const position& lhs, const position& rhs)
{
  return lhs.row*1000+lhs.col < rhs.row*1000+rhs.col;
}


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

void getStart(position& pos,vector<string> map){
    for (int row = 0; row < map.size(); row++)    
    {
        for (int col = 0; col < map[row].length(); col++)
        {
            if(map[row][col] == 'S'){
                pos.row = row;
                pos.col = col;
            }
        }     
    }
}

bool moveRight(position pos, set<position>& allPositions,vector<string> map){
    if(pos.col < map[0].length()-1){
        pos.col++;
        if(map[pos.row][pos.col] == '.'){
            allPositions.insert(pos);
        }
    }    
}

void moveDown(position pos, set<position>& allPositions,vector<string> map){
    if(pos.row < map.size()-1){
        pos.row++;
        if(map[pos.row][pos.col] == '.'){
            allPositions.insert(pos);
        }
    }
}

void moveLeft(position pos, set<position>& allPositions,vector<string> map){
    if(pos.col > 0){
        pos.col--;
        if(map[pos.row][pos.col] == '.'){
            allPositions.insert(pos);
        }
    }
}

void moveUpp(position pos, set<position>& allPositions,vector<string> map){
    if(pos.row > 0){
        pos.row--;
        if(map[pos.row][pos.col] == '.'){
            allPositions.insert(pos);
        }
    }
}

void moveAll(position pos, set<position>& allPositions,vector<string> map){
    moveUpp(pos,allPositions,map);
    moveDown(pos,allPositions,map);
    moveLeft(pos,allPositions,map);
    moveRight(pos,allPositions,map);
}

int main(){
    fstream input("input.txt");
    vector<string> map,evenMap,oddMap;
    position start;
    std::set<position> evenPos, oddPos;
    ofstream evenStep("even.txt"),oddStep("odd.txt");

    
    getMap(input,map);
    evenMap = map;
    oddMap = map;
    getStart(start,map);
    evenPos.insert(start);
    int steps = 0;    
    while (steps < 64)    
    {
        for (auto e : evenPos)
        {
            moveAll(e,oddPos,map);
        }
        steps++;
        cout << steps <<" Even:" << evenPos.size() << " Odd:" << oddPos.size() << endl;
        for (auto o : oddPos)
        {
            moveAll(o,evenPos,map);
        }
        steps++;
        cout << steps <<" Even:" << evenPos.size() << " Odd:" << oddPos.size() << endl;
    }  

    for (auto e : evenPos)
    {
        evenMap[e.row][e.col] = 'e';
    } 
    for (auto o : oddPos)
    {
        evenMap[o.row][o.col] = 'o';
    }  
    for (auto i : evenMap)
    {
        evenStep << i << endl;
    }
    
    
    cout << "Even:" << evenPos.size() << " Odd:" << oddPos.size() << endl;
    return 0;
}