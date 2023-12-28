#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<int> getNumbersFromString(string str);
int getNextGen(vector<int> invec);
bool vectorAllZero(vector<int> vec);

vector<int> getNumbersFromString(string str){
    int number;
    vector<int> numbers;
    stringstream buffStream, second;
    buffStream.str(str);
    
    while(!buffStream.eof()){
        buffStream >> number;
        numbers.push_back(number);
    }
    return numbers;
}

bool vectorAllZero(vector<int> vec){
    for (int i : vec)
    {
        if(i != 0){
            return false;
        }
    }
    return true;
}

int getNextGen(vector<int> invec){
    vector<int> next;
    int past = 0;
    for (int i = 1; i < invec.size(); i++)
    {
        next.push_back(invec[i] - invec[i-1]);
    }
    if(vectorAllZero(next)){
        past = invec.front() - next.front();
    } else{
        past = invec.front() - getNextGen(next);    
    }  
    return past;
}

int main(){
    fstream input("input.txt");
    string lines;
    vector<int> startNrs;
    int past = 0;
    
    while (!input.eof())
    {
        getline(input,lines);
        startNrs = getNumbersFromString(lines);
        past += getNextGen(startNrs);
    }
    
    cout << "Added past: " << past << endl; 
    
}