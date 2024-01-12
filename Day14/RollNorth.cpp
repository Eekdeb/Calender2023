#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

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

int main(){
    fstream input("input.txt");

    vector<string> map,mapT;
    getMap(input,map);
    transform(map,mapT);
    int moveCount = 0;
    int points = 0;
    for (auto &&m : mapT)
    {
        //cout << m << endl;
        moveCount = 0;
        for (int i = 0; i < m.length(); i++)
        {
            if(m[i] == '.') moveCount++;
            if(m[i] == '#') moveCount = 0;
            if(m[i] == 'O'){
                m[i] = '.';
                m[i-moveCount] = 'O';
                points += m.length()-i+moveCount;
            } 
        }
        cout << points << endl;   
    }
    cout << "Final point count: " << points << endl;
    return 0;
}