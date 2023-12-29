#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct starPos
{
    int row;
    int column;
}row,column;


vector<string> readFileAddemptyRows(fstream& input){
    string line;
    vector<string> map;
    bool emptyline = true;
    while (!input.eof())
    {
        emptyline = true;
        getline(input,line);
        map.push_back(line);
        for (int i = 0; i < line.length(); i++)
        {
           if(line[i] != '.'){
                emptyline = false;
                break;
           }
        }
        if(emptyline){
            map.push_back(line);
        }
    }
    
}

int main(){
    fstream input("input.txt");
    ofstream out("out.txt");

    string line;
    vector<string> map;
    bool emptyline = true;
    while (!input.eof())
    {
        emptyline = true;
        getline(input,line);
        map.push_back(line);

        for (int i = 0; i < line.length(); i++)
        {
           if(line[i] != '.'){
                emptyline = false;
                break;
           }
        }

        if(emptyline){
            map.push_back(line);
        }
    }

    bool emptyColumn = true;
    for (int i = 0; i < map.front().length(); i++)
    {
        bool emptyColumn = true;
        for (auto &&v : map)
        {
            if(v[i] != '.'){
                emptyColumn = false;
                break;
            }
        }
        if(emptyColumn){
            for (auto &&v : map)
            {
                v.insert(v.begin()+i,'.');
            }
            i = i+1;
        }
    }

    for (int i = 0; i < map.size(); i++)
    {
        out << map[i] << endl;
    }

    //get all indexes for the stars
    vector<starPos> starIndexes;
    starPos in;
    for (size_t i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[j].length(); j++)
        {
            if(map[i][j] == '#'){
                in.row = i;
                in.column = j;
                starIndexes.push_back(in);
            }
        }
    }

    long long totalDistance = 0;
    //find distance between every star
    while (!starIndexes.empty())
    {
        for (int i = 1; i < starIndexes.size(); i++)
        {
            totalDistance += abs(starIndexes[0].row-starIndexes[i].row) + abs(starIndexes[0].column - starIndexes[i].column);
        }  
        starIndexes.erase(starIndexes.begin());
    }
    cout << totalDistance << endl;
}