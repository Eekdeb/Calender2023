#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(){
    fstream in("out.txt");
    fstream in2("out2.txt");
    ofstream diff("diff.txt");
    string buff,buff2,diffs;

    while (!in.eof() && !in2.eof())
    {
        getline(in,buff);
        getline(in2,buff2);
        diffs = "";
        for (int i = 0; i < buff.length(); i++)
        {
            if(buff[i] != buff2[i]){
                diffs += "#";
            } else diffs += ".";
        }
        diff << diffs << "\n"; 
    }
    
}