#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct position{
    int x;
    int y;
    char dir;
};

void move(char dir, int& x, int& y){
    if(dir == 'U') y -= 1;
    if(dir == 'D') y += 1;
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

char updateDir(char prev, char current){
    if(prev == current) return prev;
    if(prev == 'D'){
        if(current == 'R') return 'U';
        if(current == 'L') return 'D';
    }
    if(prev == 'U'){
        if(current == 'R') return 'D';
        if(current == 'L') return 'U';
    }
    if(prev == 'R'){
        if(current == 'U') return 'L';
        if(current == 'D') return 'R';
    }
    if(prev == 'L'){
        if(current == 'U') return 'R';
        if(current == 'D') return 'L';
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

    //get the outer positions and the max and min positions
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
            positions.push_back({x,y,dir});
        }
    }

    //create a map witht the right size
    getMap(yMax+abs(yMin)+1,xMax+abs(xMin)+1,draw);

    for (auto i : positions)
    {
        draw[i.y+abs(yMin)][i.x+abs(xMin)] = '#';
        if(i.x == 0){
            draw[i.y+abs(yMin)][i.x+abs(xMin)] = 'y';
        }
        if(i.y == 0){
            draw[i.y+abs(yMin)][i.x+abs(xMin)] = 'x';
        } 
        if(i.x == 0 && i.y == 0){
            draw[i.y+abs(yMin)][i.x+abs(xMin)] = '0';
        }
    }

    for (auto p : positions)
    {
        position previous;
        if(p.dir == 'R'){
            p.y++;
            while (draw[p.y+abs(yMin)][p.x+abs(xMin)] == '.')
            {
                //cout << p.y+abs(yMin) << " " << p.x+abs(xMin) << endl;
                draw[p.y+abs(yMin)][p.x+abs(xMin)] = 'K';
                p.y++;
            }
            if(previous.dir == 'D'){
                previous.y++;
                while (draw[previous.y+abs(yMin)][previous.x+abs(xMin)] == '.')
                {
                    //cout << p.y+abs(yMin) << " " << p.x+abs(xMin) << endl;
                    draw[previous.y+abs(yMin)][previous.x+abs(xMin)] = 'K';
                    previous.y++;
                }
            }
        }
        previous = p;
    }

    int digs = 0;
    for (auto d : draw)
    {
        for (int i = 0; i < d.length(); i++)
        {
            if(d[i] != '.') digs++;
        }
        
    }
    
    cout << digs << endl;

    for (auto i : draw)
    {
        out << i << endl;
    }

    /*can find the inside in two ways
    1. Raycasting is available but for the "points" we need to ignore them
          POINT IS when before and after is up or down
          This works better when you have lines and not points.
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
