/*
    This hole is a lot bigger than part1 so to draw out the hole is not realistic
    Instead i save the points in a 2d vector so a can loop though the point
    and when going right "in my case" means inward is down.*
    So take the distance between two points and you get the numbers digged

    *To make shore what is correct you can check if it goes out of bounds
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct position{
    long long x;
    long long y;
    char dir;
    
    inline bool operator== (position& pos){
        if(x == pos.x && y == pos.y)
            return true;
        return false;
    }
};

void move(char dir, long long& x, long long& y){
    if(dir == 'U') y -= 1;
    if(dir == 'D') y += 1;
    if(dir == 'R') x += 1;
    if(dir == 'L') x -= 1;
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

char strToDir(char in){
    if(in == '0') return 'R';
    if(in == '1') return 'D';
    if(in == '2') return 'L';
    if(in == '3') return 'U';
}

int main(){
    fstream input("input.txt");
    vector<position> positions;
    vector<vector<long long>> vecPos;
    long long x = 0, y = 0, xMin = 0, yMin = 0, yMax = 0, xMax = 0;
    long long holes = 0;

    char cTrash, dir;
    long iTrash, dist;
    string RGB;
    
    //get the outer positions and the max and min positions
    while (!input.eof()){
        input >> cTrash;
        input >> iTrash;
        input >> RGB;

        dist = stoi(RGB.substr(2,5), 0, 16);;
        dir = strToDir(RGB[7]);

        for (dist; dist > 0; dist--){
            move(dir,x,y);
            if(yMin > y) yMin = y;
            if(xMin > x) xMin = x;
            if(yMax < y) yMax = y;
            if(xMax < x) xMax = x;
            positions.push_back({x,y,dir});
            holes++;
        }
    }
    cout << "holds " << holes << endl;
    vector<long long> a;
    for (long long i = 0; i < xMax+abs(xMin)+1; i++)
    {
        vecPos.push_back(a);
    }

    for (auto i : positions)
    {
        vecPos[i.x+abs(xMin)].push_back(i.y+abs(yMin));
    }    
    
    for (auto p : positions)
    {
        position previous;
        if(p.dir == 'R'){
            long long next = 9999999999999999;
            //for all point in this x column
            for (auto i : vecPos[p.x+abs(xMin)])
            {
                //if y is bigger than current point
                if(p.y+abs(yMin) < i){
                    //and is the smallest until now
                    if(next > i){
                        next = i;
                    }
                }
            }
            //Add the deference between the points
            holes += next-(p.y+abs(yMin))-1;

            if(previous.dir == 'D'){
                long long next = 99999999999999999;
                for (auto i : vecPos[previous.x+abs(xMin)])
                {
                    if(previous.y+abs(yMin) < i){
                        if(next > i){
                            next = i;
                        }
                    }
                }
                holes += next-(previous.y+abs(yMin))-1;
            }
            //cout << next-(p.y+abs(yMin))-1<< " " << p.y+abs(yMin)<< " " << next<< endl;
            
        }
        previous = p;        
    }
    
    //92291468986379 to high
    cout << "Number " << holes << endl;
    
    input.close();
    return 0;
}
