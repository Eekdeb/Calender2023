#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct leaf
{
    int row;
    int col;
    char dir;
    int dirCount;
    int heatLoss;
    bool operator() (leaf i,leaf j){return i.heatLoss > j.heatLoss;}
} leafSort;

int getHash(leaf l);
void printLeaf(leaf l);

void getMap(fstream& input, vector<vector<int>>& map){
    string buff;
    vector<int> intRow;
    map.clear();
    int row = 0;
    while (input.peek() != '\n' && !input.eof())
    {
        intRow.clear();
        getline(input,buff);
        for (int i = 0; i < buff.length(); i++)
        {
            intRow.push_back(buff[i]-48);
        }
        map.push_back(intRow);
        row++;
    }
}

void updateLeaf(vector<leaf>& leafs, vector<vector<int>> map, unordered_set<int>& visited){
    leaf o = leafs.front(), newl;
    pop_heap(leafs.begin(),leafs.end(),leafSort); leafs.pop_back();
    //down
    if(o.dir != 'U' && (o.dir != 'D' || (o.dir == 'D' && o.dirCount < 3)) && o.row != map.size()-1){
        newl = o;
        if(o.dir == 'D')
            newl.dirCount++;
        else{
            newl.dir = 'D';
            newl.dirCount = 1;
        }
        newl.row++;
        newl.heatLoss += map[newl.row][newl.col];
        //check if it already exists.
        auto s = visited.insert(getHash(newl));
        if(s.second){
            leafs.push_back(newl); push_heap(leafs.begin(),leafs.end(),leafSort);
        }
    }
    //Right
    if(o.dir != 'L' && (o.dir != 'R' || (o.dir == 'R' && o.dirCount < 3)) && o.col != map[0].size()-1){
        newl = o;
        if(o.dir == 'R')
            newl.dirCount++;
        else{
            newl.dir = 'R';
            newl.dirCount = 1;
        }
        newl.col++;
        newl.heatLoss += map[newl.row][newl.col];
        auto s = visited.insert(getHash(newl));
        if(s.second){
            leafs.push_back(newl); push_heap(leafs.begin(),leafs.end(),leafSort);
        }
    }
    //Upp
    if(o.dir != 'D' && (o.dir != 'U' || (o.dir == 'U' && o.dirCount < 3)) && o.row != 0){
        newl = o;
        if(o.dir == 'U')
            newl.dirCount++;
        else{
            newl.dir = 'U';
            newl.dirCount = 1;
        }
        newl.row--;
        newl.heatLoss += map[newl.row][newl.col];
        //check if it already exists.
        auto s = visited.insert(getHash(newl));
        if(s.second){
            leafs.push_back(newl); push_heap(leafs.begin(),leafs.end(),leafSort);
        }
    }
    //Left
    if(o.dir != 'R' && (o.dir != 'L' || (o.dir == 'L' && o.dirCount < 3)) && o.col != 0){
        newl = o;
        if(o.dir == 'L')
            newl.dirCount++;
        else{
            newl.dir = 'L';
            newl.dirCount = 1;
        }
        newl.col--;
        newl.heatLoss += map[newl.row][newl.col];
        auto s = visited.insert(getHash(newl));
        if(s.second){
            leafs.push_back(newl); push_heap(leafs.begin(),leafs.end(),leafSort);
        }
    }
}

void printLeaf(leaf l){
    cout << "pos: (" << l.row << "," << l.col << ") Heat: " << l.heatLoss << 
        " Dir: " << l.dir << " " << l.dirCount << endl;
}

int getHash(leaf l){
    // 111 -> 111000 -> 111222 -> 11122200 -> 11122248 -> 111222480
    int hash = l.row;
    hash *= 1000;
    hash += l.col;
    hash *= 100;
    hash += l.dir;
    hash *= 10;
    hash += l.dirCount;
    return hash;
}

int main(){
    fstream input("input.txt");
    vector<vector<int>> map;
    unordered_set<int> visited;
    getMap(input,map);
    
    vector<leaf> leafs;
    
    leaf start = {0,0,'A',0,0},l,newl;
    leafs.push_back(start);
    make_heap(leafs.begin(),leafs.end(),leafSort);
    int count = 0;
    while(!leafs.empty() && count < 10){
        //count++;
        //printLeaf(leafs[0]);
        //cout << getHash(leafs[0]) << endl;
        if(leafs[0].row == map.size()-1 && leafs[0].col == map[0].size()-1){
            printLeaf(leafs[0]);
        }
        updateLeaf(leafs,map,visited);
    }
}