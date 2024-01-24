#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <bits/stdc++.h>
#include<windows.h>

using namespace std;

void printMap(vector<string> map);

struct light
{
    int row;
    int col;
    char dir;
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

void moveUpp(light& l, vector<string> map){
    if(l.row == 0){
        l.dir = 'X';
        return;
    }
    l.row--;  
    if(map[l.row][l.col] == 'X'){
        l.dir = 'X';
        return;
    }
    if(map[l.row][l.col] == '\\'){
        l.dir = 'L';
    }
    if(map[l.row][l.col] == '/'){
        l.dir = 'R';
    }
    if(map[l.row][l.col] == '-'){
        l.dir = 'S';
    }
}

void moveDown(light& l, vector<string> map){
    if(l.row == map.size()-1){
        l.dir = 'X';
        return;
    }
    l.row++;
    if(map[l.row][l.col] == 'X'){
        l.dir = 'X';
        return;
    }  
    if(map[l.row][l.col] == '\\'){
        l.dir = 'R';
    }
    if(map[l.row][l.col] == '/'){
        l.dir = 'L';
    }
    if(map[l.row][l.col] == '-'){
        l.dir = 'S';
    }
}

void moveLeft(light& l, vector<string> map){
    if(l.col == 0){
        l.dir = 'X';
        return;
    }
    l.col--; 
    if(map[l.row][l.col] == 'X'){
        l.dir = 'X';
        return;
    } 
    if(map[l.row][l.col] == '\\'){
        l.dir = 'U';
    }
    if(map[l.row][l.col] == '/'){
        l.dir = 'D';
    }
    if(map[l.row][l.col] == '|'){
        l.dir = 'S';
    }
}

void moveRight(light& l, vector<string> map){
    if(l.col == map[0].length()){
        l.dir = 'X';
        return;
    }
    l.col++;  
    if(map[l.row][l.col] == 'X'){
        l.dir = 'X';
        return;
    }
    if(map[l.row][l.col] == '\\'){
        l.dir = 'D';
    }
    if(map[l.row][l.col] == '/'){
        l.dir = 'U';
    }
    if(map[l.row][l.col] == '|'){
        l.dir = 'S';
    }
}

void savePath(light l, vector<string> map, vector<string>& hasBeen){
    if(map[l.row][l.col] == 'X'){
        hasBeen[l.row][l.col] = 'X'; 
        return;
    } 
    if(map[l.row][l.col] == '/') hasBeen[l.row][l.col] = '/';
    if(map[l.row][l.col] == '\\') hasBeen[l.row][l.col] = '\\';
    if(map[l.row][l.col] == '-') hasBeen[l.row][l.col] = '-';
    if(map[l.row][l.col] == '|') hasBeen[l.row][l.col] = '|';
    if(map[l.row][l.col] == '.') hasBeen[l.row][l.col] = l.dir;
}

void moveLights(vector<light>& lights, vector<string> map, vector<string>& hasBeen){
    int count = 0;
    int nrOfLights = lights.size();
    vector<int> lightsToRemove;
    //cout << nrOfLights << endl;
    while (nrOfLights != 0 && count < 10000)
    {
        cout << nrOfLights << " " << count << endl;
        count++;
        //Sleep(500);
        //printMap(hasBeen);
        //cout << endl;
        for (int i = 0; i < nrOfLights; i++)        
        {
            //cout << lights[i].row << "," << lights[i].col << endl;
            savePath(lights[i],map,hasBeen);
            //hasBeen[lights[i].row][lights[i].col] = '#';
            switch (lights[i].dir)
            {
            case 'U':
                moveUpp(lights[i],map);
                break;
            case 'D':
                moveDown(lights[i],map);
                break;
            case 'L':
                moveLeft(lights[i],map);
                break;
            case 'R':
                moveRight(lights[i],map);
                break;
            case 'S':
                light new1,new2;
                new1.col = lights[i].col;
                new1.row = lights[i].row;
                new2.col = lights[i].col;
                new2.row = lights[i].row;
                if(map[lights[i].row][lights[i].col] == '-'){
                    map[lights[i].row][lights[i].col] = 'X';
                    new1.dir = 'L';
                    new2.dir = 'R';
                    lights.push_back(new1);
                    lights.push_back(new2);
                    nrOfLights += 2;
                    lights.erase(lights.begin()+i);
                    nrOfLights--;
                }
                if(map[lights[i].row][lights[i].col] == '|'){
                    map[lights[i].row][lights[i].col] = 'X';
                    new1.dir = 'U';
                    new2.dir = 'D';
                    lights.push_back(new1);
                    lights.push_back(new2);
                    nrOfLights += 2;
                    lights.erase(lights.begin()+i);
                    nrOfLights--;
                }
                break;
            } 
            if(lights[i].dir == 'X'){
                //savePath(lights[i],map,hasBeen);
                lightsToRemove.push_back(i);
            }       
        }   
        //remove lights on deadends
        sort(lightsToRemove.begin(),lightsToRemove.end(),greater<int>());
        for (int i : lightsToRemove)
        {
            lights.erase(lights.begin()+i);
            nrOfLights--;
        }
        lightsToRemove.clear();
    }
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
    cout << input[0].length() << " " << output[0].length() << endl;
}

void printMap(vector<string> map){
    for (auto i : map)
    {
        cout << i << endl;        
    }  
}

light initLight(vector<string> map, int row, int col){
    light start;
    start.col = row;
    start.row = col;
    start.dir = 'R';
    if(map[row][col] == '\\') start.dir = 'D';
    if(map[row][col] == '/') start.dir = 'U';
    if(map[row][col] == '|') start.dir = 'S';
    return start;
}

int main(){
    fstream input("example.txt");
    ofstream out("out.txt");
    string buff;
    vector<string> map, drawMap;
    getMap(input,map);
    getSameSizeMap(map,drawMap);
    light start;
    start = initLight(map,0,0);


    vector<light> lights;
    lights.push_back(start);
    moveLights(lights,map,drawMap);
    
    int visited = 0;
    for (auto m : drawMap)
    {
        for (int i = 0; i < m.length(); i++)
        {
            if(m[i] != '.'){
                visited++;
            }
        }
    }
    //cout << drawMap[0].length();
    //printMap(map);
    //printMap(drawMap);
    //8941
    //8914 high
    //8901 right
    //8900 low
    cout << visited << endl;
    for (auto i : drawMap)
    {
        out << i << endl;        
    } 

    out.close();
    input.close();
    /*  WAYS OF MAKING LIGHT
        Every light is its own. (This is better because with the lights collision no redoing is done)
            got a direction and position.
            all light move simontaniosly one step ad a time. 
            ends when all lights have died.
            dies when going out of bounds or head on collision
        
        One light at a time (with a GPU this would be my choice because lights are independent)
            one light is taking steps
            save the position and direction when light splits
            light dies when out of bounds or split already visited
            when light dies continue with last saved.
            ends when no more are saved

    */
}