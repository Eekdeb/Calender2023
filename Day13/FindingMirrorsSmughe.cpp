#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void NextMap(fstream& input, vector<string>& map);
void transform(vector<string> input, vector<string>& output);
int compareOffset(string s1, string s2);

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

int validMirror(vector<string> map, int start, int end){
    //bool valid = true;
    int differences = 0;
    for (int i = start, j = end; i < j; i++, j--)
    {
        differences += compareOffset(map[i],map[j]);
    }
    return differences;
}

int getMirrorValue(vector<string> map){
    string first,last;
    first = map[0];
    last = map[map.size()-1];
    int totalPoints = 0;
    int differences = 0;
    //check if it is from top
    for (int i = 1; i < map.size()-1; i += 2)
    {
        differences = 0;
        differences += compareOffset(map[i],first);
        if(differences <= 1){
            differences += validMirror(map,1,i-1);
            if(differences == 1){
                //cout << i << "a  " << differences << endl;
                totalPoints += ((i+1)/2); 
            }
        }

        differences = 0;
        differences += compareOffset(map[i],last);
        if(differences <= 1){
            differences += validMirror(map,i+1,map.size()-2);
            if(differences == 1){
                //cout << i << "  " << differences;
                totalPoints += ((map.size()+i)/2); 
            }
        }
    }
    return totalPoints;
}

int compareOffset(string s1, string s2){
    int count = 0;
    for (int i = 0; i < s1.length(); i++)
    {
        if(s1[i] != s2[i]){
            count++;
        }
    }
    return count;
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
        
        for (auto i : mapT)
        {
            //cout << i << endl;
        }
        

        first = mapT[0];
        last = mapT[mapT.size()-1];
        points += getMirrorValue(mapT);
        
    }
    //low 12361
    cout << "Points " << points << endl;
    input.close();
}