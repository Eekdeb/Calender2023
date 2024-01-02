#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void getInputFromLine(string in, string& out, vector<int>& nrsOut){
    stringstream ss(in);
    char bin;
    int nr;
    ss >> out;
    while (!ss.eof())
    {
        ss >> nr;
        ss >> bin;
        nrsOut.push_back(nr);
    }
    
}

int main(){
    fstream input("input.txt");
    string buff;
    
    string code;
    vector<int> numbers;
    getline(input,buff);
    getInputFromLine(buff,code,numbers);
    cout << code << endl;
    cout << numbers[2] << endl;
    
}