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
    int uppCount;
    int rightCount;
    int downCount;
    int leftCount;
    int nrOfSteps;
    bool operator() (LEAF i,LEAF j) { return (i.value<j.value);}
} leaf;

void insetSort(vector<LEAF>& vec, LEAF ins);

bool stepsSort(LEAF i, LEAF j) {return (i.nrOfSteps < j.nrOfSteps);}

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
        intVec.push_back(INT32_MAX);
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

void outMap(vector<vector<int>> map, ofstream& out){
    for (auto i : map)
    {
        for (auto j : i)
        {
            out << j << " ";
        }
        out << "\n";    
    }
}

void updateLeaf(vector<LEAF>& leafs, vector<vector<int>> map, vector<vector<int>>& pathMap){
    LEAF origin = leafs[0], newl;
    int ofsett = 3;
    //right
    if(origin.col != map[0].size()-1){
        newl = {
            origin.row,
            origin.col+1,
            origin.value + map[origin.row][origin.col+1],
            0,origin.rightCount +1,0,0,origin.nrOfSteps+1
            };
        if(newl.value - ofsett <= pathMap[origin.row][origin.col+1] && newl.rightCount <= 3){
            insetSort(leafs,newl);
            if(newl.value < pathMap[origin.row][origin.col+1])
                pathMap[origin.row][origin.col+1] = newl.value;
        }
    }
    //Left
    if(origin.col != 0){
        newl = {
            origin.row,
            origin.col-1,
            origin.value + map[origin.row][origin.col-1],
            0,0,0,origin.leftCount+1,origin.nrOfSteps+1
            };
        if(newl.value - ofsett <= pathMap[origin.row][origin.col-1] && newl.leftCount <= 3){
            insetSort(leafs,newl);
            if(newl.value < pathMap[origin.row][origin.col-1])
                pathMap[origin.row][origin.col-1] = newl.value;
        }
    }
    //Down
    if(origin.row != map.size()-1){
        newl = {
            origin.row+1,
            origin.col,
            origin.value + map[origin.row+1][origin.col],
            0,0,origin.downCount+1,0,origin.nrOfSteps+1
            };
        if(newl.value - ofsett <= pathMap[origin.row+1][origin.col] && newl.downCount <= 3){
            insetSort(leafs,newl);
            if(newl.value < pathMap[origin.row+1][origin.col])
                pathMap[origin.row+1][origin.col] = newl.value;
        }
    }
    //Upp
    if(origin.row != 0){
        newl = {
            origin.row-1,
            origin.col,
            origin.value + map[origin.row-1][origin.col],
            origin.uppCount+1,0,0,0,origin.nrOfSteps+1
            };
        if(newl.value - ofsett <= pathMap[origin.row-1][origin.col] && newl.uppCount <= 3){
            insetSort(leafs,newl);
            if(newl.value < pathMap[origin.row-1][origin.col])
                pathMap[origin.row-1][origin.col] = newl.value;
        }
    }
}

void insetSort(vector<LEAF>& vec, LEAF ins){
    auto lower = lower_bound(vec.begin(), vec.end(), ins,leaf);
    int index = distance(vec.begin(), lower);
    vec.insert(vec.begin()+index,ins);
}

int main(){
    fstream input("input.txt");
    ofstream out("out.txt");
    vector<vector<int>> map, pathMap;
    getMap(input,map);
    getSameSizeMap(map,pathMap);
    

    vector<LEAF> leafs;
    LEAF start = {0,0,0,0,0,0,0,0};
    leafs.push_back(start);

    int count = 0;
    while(!leafs.empty() && pathMap[pathMap.size()-1][pathMap[0].size()-1] == INT32_MAX){
        count++;
        updateLeaf(leafs,map,pathMap);
        leafs.erase(leafs.begin(),leafs.begin()+1);
        if(leafs.size() > 100000){
            sort(leafs.begin(),leafs.end(),stepsSort);
            leafs.erase(leafs.begin(),leafs.begin()+90000);
            sort(leafs.begin(),leafs.end(),leaf);
        }
        //sort(leafs.begin(), leafs.end(),leaf);
        //cout << leafs[0].value << endl;
        if(count % 1000 == 0){
            cout << count << endl;
        }
    } 
    outMap(pathMap,out);
    cout << pathMap[pathMap.size()-1][pathMap[0].size()-1] << endl;
    //printMap(pathMap);
}