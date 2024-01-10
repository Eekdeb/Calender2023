#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void NextMap(fstream& input, vector<string>& map);
void transform(vector<string> input, vector<string>& output);

void getNextMap(fstream& input, vector<string>& map){
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

bool validMirror(vector<string> map, int start, int end){
    bool valid = true;
    for (int i = start, j = end; i < j; i++, j--)
    {
        if(map[i].compare(map[j]) != 0) valid = false;
        //cout << i << " " << j << " " << valid << endl;
    }

    for (int i = start, j = end; i > j; i--, j++)
    {
        if(map[i].compare(map[j]) != 0) valid = false;
        //cout << i << " " << j << " " << valid << endl;
    }
    return valid;
}

int getMirrorValue(vector<string> map){
    string first,last;
    first = map[0];
    last = map[map.size()-1];
    int totalPoints = 0;
    //check if it is from top
    for (int i = 1; i < map.size()-1; i += 2)
    {
        if(map[i].compare(first) == 0 && validMirror(map,0,i)){
            //cout << first << " " << map[i] << " " << i << endl;
            //cout << "f size " << ((i+1)/2) << endl;;
            totalPoints += ((i+1)/2); 
        }
        if(map[i].compare(last) == 0 && validMirror(map,i,map.size()-1)){
            //cout << "l size " << ((map.size()+i)/2) << " " << i << endl;
            totalPoints += ((map.size()+i)/2);
        }
    }
    return totalPoints;
}

int main(){
    fstream input("input.txt");
    string buff;
    string first,last;
    vector<string> map;
    vector<string> mapT;
    int points = 0, oldPoints = 0;

    //getNextMap(input,map);
    //map.clear();


    while (!input.eof())
    {
        getNextMap(input,map);

        points += getMirrorValue(map) * 100;
        
        //cout << "Transforming" << endl;
        transform(map,mapT); 
        
        first = mapT[0];
        last = mapT[mapT.size()-1];
        points += getMirrorValue(mapT);
        
    }
    //low 41856
    cout << "Points " << points << endl;
    input.close();
}