#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct LEAF
{
    int row;
    int col;
    int value;

    bool operator() (LEAF i,LEAF j) { return (i.value<j.value);}
} leaf;


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

void getSameSizeMap(vector<vector<int>> input, vector<vector<int>>& output){
    vector<int> intVec;
    for (int i = 0; i < input[0].size(); i++)
    {
        intVec.push_back(INT8_MAX);
    }
    for(int i = 0; i < input.size(); i++){
        output.push_back(intVec);
    }
}

void printMap(vector<vector<int>> map){
    for (auto i : map)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << "\n";    
    }
}

void updateLeaf(vector<LEAF>& leafs, vector<vector<int>> map, vector<vector<int>>& pathMap){
    LEAF origin = leafs[0], newl;
    //right
    if(origin.col != map[0].size()-1){
        newl = {origin.row,origin.col+1,origin.value + map[origin.row][origin.col+1]};
        if(newl.value < pathMap[origin.row][origin.col+1]){
            leafs.push_back(newl);
            pathMap[origin.row][origin.col+1] = newl.value;
        }
    }
    //Left
    if(origin.col != 0){
        newl = {origin.row,origin.col-1,origin.value + map[origin.row][origin.col-1]};
        if(newl.value < pathMap[origin.row][origin.col-1]){
            leafs.push_back(newl);
            pathMap[origin.row][origin.col-1] = newl.value;
        }
    }
    //Down
    if(origin.row != map.size()-1){
        newl = {origin.row+1,origin.col,origin.value + map[origin.row+1][origin.col]};
        if(newl.value < pathMap[origin.row+1][origin.col]){
            leafs.push_back(newl);
            pathMap[origin.row+1][origin.col] = newl.value;
        }
    }
    //Upp
    if(origin.row != 0){
        newl = {origin.row-1,origin.col,origin.value + map[origin.row-1][origin.col]};
        if(newl.value < pathMap[origin.row-1][origin.col]){
            leafs.push_back(newl);
            pathMap[origin.row-1][origin.col] = newl.value;
        }
    }
}

int main(){
    fstream input("example.txt");
    vector<vector<int>> map, pathMap;
    getMap(input,map);
    getSameSizeMap(map,pathMap);
    

    vector<LEAF> leafs;
    LEAF start = {0,0,0};
    leafs.push_back(start);

    while(!leafs.empty() && pathMap[pathMap[0].size()-1][pathMap.size()-1] == INT8_MAX){
        updateLeaf(leafs,map,pathMap);
        leafs.erase(leafs.begin(),leafs.begin()+1);
        sort(leafs.begin(), leafs.end(),leaf);
    } 
    printMap(pathMap);
}