#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int getSmalest(int nr1, int nr2){
    if(nr1 > nr2){
        return nr2;
    } 
    return nr1;
}
int getBiggest(int nr1, int nr2){
    if(nr1 > nr2){
        return nr1;
    } 
    return nr2;
}

struct starPos
{
    int row;
    int column;
}row,column;

int main(){
    fstream input("input.txt");
    ofstream out("out.txt");

    //read file
    string line, lineE = "";
    bool initEmptyLine = false;
    vector<string> map;
    bool emptyline = true;
    while (!input.eof())
    {
        emptyline = true;
        getline(input,line);

        if(!initEmptyLine){
            initEmptyLine = true;
            for (int i = 0; i < line.length(); i++)
            {
                lineE += "E";
            }
        }

        for (int i = 0; i < line.length(); i++)
        {
           if(line[i] != '.'){
                emptyline = false;
                break;
           }
        }

        if(emptyline){
            map.push_back(lineE);
        } else{
            map.push_back(line);
        }
    }

    //add empty column stuff
    bool emptyColumn = true;
    for (int i = 0; i < map.front().length(); i++)
    {
        bool emptyColumn = true;
        for (auto &&v : map)
        {
            if(v[i] != '.' && v[i] != 'E'){
                emptyColumn = false;
                break;
            }
        }
        if(emptyColumn){
            for (auto &&v : map)
            {
                v.erase(v.begin()+i);
                v.insert(v.begin()+i,'E');
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
    int bigRow=0, bigCol=0, smalRow = 0, smalCol = 0;
    //find distance between every star E = 1000000 steps
    while (!starIndexes.empty())
    {
        for (int i = 1; i < starIndexes.size(); i++)
        {
            bigRow = getBiggest(starIndexes[0].row,starIndexes[i].row);
            bigCol = getBiggest(starIndexes[0].column,starIndexes[i].column);
            smalRow = getSmalest(starIndexes[0].row,starIndexes[i].row);
            smalCol = getSmalest(starIndexes[0].column,starIndexes[i].column);
            
            for (int i = smalRow; i < bigRow; i++)
            {
                if(map[i][0] == 'E'){
                    totalDistance += 999999;
                }
            }
            for (int i = smalCol; i < bigCol; i++)
            {
                if(map[0][i] == 'E'){
                    totalDistance +=999999;
                }
            }
            totalDistance += bigRow-smalRow + bigCol-smalCol;           
        }  
        starIndexes.erase(starIndexes.begin());
    }
    cout << totalDistance << endl;
}