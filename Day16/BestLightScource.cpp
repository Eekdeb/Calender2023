#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void getMap(fstream& input, vector<string>& map);

struct light
{
    int row;
    int col;
    char dir;
    bool moving;
};

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

void getSameSizeMap(vector<string> input, vector<string>& output){
    string lineForDrawMap = "";
    for (int i = 0; i < input[0].length(); i++)
    {
        lineForDrawMap += ".";
    }
    for(int i = 0; i < input.size(); i++){
        output.push_back(lineForDrawMap);
    }
    //cout << input[0].length() << " " << output[0].length() << endl;
}

bool moveRight(light& l,vector<string> map){
    if(l.col < map[0].length()-1){
        l.col++;
        return true;
    }    
    return false;
}

bool moveDown(light& l,vector<string> map){
    if(l.row < map.size()-1){
        l.row++;
        return true;
    }
    return false;
}

bool moveLeft(light& l,vector<string> map){
    if(l.col > 0){
        l.col--;
        return true;
    }
    return false;
}

bool moveUpp(light& l,vector<string> map){
    if(l.row > 0){
        l.row--;
        return true;
    }
    return false;
}

void moveDir(light& l,vector<string> map){
    bool moving = false;
    if(l.moving){
        if(l.dir == 'U') moving = moveUpp(l,map);
        if(l.dir == 'D') moving = moveDown(l,map);
        if(l.dir == 'L') moving = moveLeft(l,map);
        if(l.dir == 'R') moving = moveRight(l,map);
    }
    if(!moving){
        l.moving = false;
    }
}

void changeDir(light& l, vector<string> map){
    if(map[l.row][l.col] == '\\'){
        if(l.dir == 'R'){
            l.dir = 'D';
        }
        else if(l.dir == 'D'){
            l.dir = 'R';
        }
        else if(l.dir == 'U'){
            l.dir = 'L';
        }
        else if(l.dir == 'L'){
            l.dir = 'U';
        }   
    }
    if(map[l.row][l.col] == '/'){
        if(l.dir == 'R'){
            l.dir = 'U';
        }
        else if(l.dir == 'D'){
            l.dir = 'L';
        }
        else if(l.dir == 'U'){
            l.dir = 'R';
        }
        else if(l.dir == 'L'){
            l.dir = 'D';
        }   
    }
    if(map[l.row][l.col] == 'V'){
        l.moving = false;
    }
}

void newLights(vector<light>& newLights, light& origen, vector<string>& map){
    if(map[origen.row][origen.col] == '|' && (origen.dir == 'L' || origen.dir == 'R')){
        light n;
        if(origen.row > 0){
            n = {origen.row-1,origen.col,'U',true};
            newLights.push_back(n);
        }
        if(origen.row < map.size()-1){
            n = {origen.row+1,origen.col,'D',true};
            newLights.push_back(n);
        }
        map[origen.row][origen.col] = 'V';
        origen.moving = false;
    }
    if(map[origen.row][origen.col] == '-' && (origen.dir == 'U' || origen.dir == 'D')){
        light n;
        if(origen.col > 0){
            n = {origen.row,origen.col-1,'L',true};
            newLights.push_back(n);
        }
        if(origen.col < map[0].length()-1){
            n = {origen.row,origen.col+1,'R',true};
            newLights.push_back(n);
        }
        map[origen.row][origen.col] = 'V';
        origen.moving = false;
    }
}

void drawPlace(vector<string>& map, light l){
    map[l.row][l.col] = '#';
}

int letLightTravel(light start,vector<string> map){
    vector<light> lights, lightsTemp;
    vector<string> outMap;
    getSameSizeMap(map,outMap);
    lights.push_back(start);
    int stopCount = 0;

    while (!lights.empty())    
    {
        stopCount = 0;
        for (auto &&l : lights){
            if(l.moving){
                drawPlace(outMap,l);
                changeDir(l,map);
                newLights(lightsTemp,l,map);
                moveDir(l,map);
            } else{
                stopCount++;
            }
        }
        if(stopCount == lights.size()){
            lights.clear();
            for (auto &&l : lightsTemp)
            {
                lights.push_back(l);
            }
            lightsTemp.clear();
        }
    }
    //count visited places
    int visited = 0;
    for (auto m : outMap)
    {
        for (int i = 0; i < m.length(); i++)
        {
            if(m[i] != '.'){
                visited++;
            }
        }
    }
    return visited;
}

int main(){
    fstream input("example.txt");
    vector<string> map;
    getMap(input,map);
    light start {0,0,'R',true};

    vector<light> startingPlaces;

    for (int i = 0; i < map.size(); i++)
    {
        start.row = i;
        start.col = 0;
        start.dir = 'R';
        startingPlaces.push_back(start);
        start.col = map[0].length();
        start.dir = 'L';
        startingPlaces.push_back(start);
        
    }
    for (int i = 0; i < map[0].length(); i++)
    {
        start.row = 0;
        start.col = i;
        start.dir = 'D';
        startingPlaces.push_back(start);
        start.row = map.size()-1;
        start.dir = 'U';
        startingPlaces.push_back(start);
        
    }
    
    int visited = 0, visT = 0;
    for (auto i : startingPlaces)
    {
        visT = letLightTravel(i,map);
        if(visT > visited){
            visited = visT;
            cout << visited << endl;
        }
    }
     
    cout << visited << endl;
}