#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct position
{
    int x;
    int y;
};


void move(char dir, int& x, int& y){
    if(dir == 'U') y += 1;
    if(dir == 'D') y -= 1;
    if(dir == 'R') x += 1;
    if(dir == 'L') x -= 1;
}

void getMap(int rows, int cols, vector<string>& map){
    string lineForDrawMap = "";
    for (int i = 0; i < cols; i++)
    {
        lineForDrawMap += ".";
    }
    for(int i = 0; i < rows; i++){
        map.push_back(lineForDrawMap);
    }
}

int main(){
    fstream input("input.txt");
    ofstream out("out.txt");
    vector<position> positions;
    vector<string> draw;
    int x = 0, y = 0, xMin = 0, yMin = 0, yMax = 0, xMax = 0;

    char dir;
    int dist;
    string RGB;
    
    int count = 0;
    while (!input.eof()){
        count++;
        input >> dir;
        input >> dist;
        input >> RGB;
        //cout << "Dir: " << dir << " Dist: " << dist << " RGB: " << RGB << endl;
        for (dist; dist > 0; dist--){
            move(dir,x,y);
            if(yMin > y) yMin = y;
            if(xMin > x) xMin = x;
            if(yMax < y) yMax = y;
            if(xMax < x) xMax = x;
            positions.push_back({x,y});
        }
    }
    cout << yMax+abs(yMin) << " " << xMax+abs(xMin) << endl;

    getMap(yMax+abs(yMin)+1,xMax+abs(xMin)+1,draw);

    cout << draw.size() << " " << draw[0].length() << endl;

    for (auto i : positions)
    {
        //cout << i.y+abs(yMin) << " " << i.x+abs(xMin) << endl;
        draw[i.y+abs(yMin)][i.x+abs(xMin)] = '#';
    }
    
    for (auto i : draw)
    {
        out << i << endl;
    }

    /*can find the inside in two ways
    1. Raycasting is available but for the "points" we need to ignore them
          POINT IS when before and after is up or down
          ex #...# or ######
             #####    #....#
    2. The same as day10, have a direction and folow it all round.
        ex ##### From S going up keep Right and fill in
           #...#
           #...S
           #####
    */
    out.close();
    input.close();
    return 0;
}
