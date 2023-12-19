#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<int> getNumbersFromString(string str){
    int number;
    vector<int> numbers;
    stringstream buffStream;
    buffStream.str(str);
    
    while(!buffStream.eof()){
        buffStream >> number;
        numbers.push_back(number);
    }
    return numbers;
}

int main(){
    fstream input ("input.txt");
    //fstream input ("exampleInput.txt");
    input.ignore(256,' ');

    vector<int> times, distance;
    string buff;
    
    getline(input,buff);
    times = getNumbersFromString(buff);
    input.ignore(256,':');
    getline(input,buff);
    distance = getNumbersFromString(buff);
    int winns = 0;
    int combo = 1;
    for (int i = 0; i < times.size(); i++)
    {
        for (int j = 0; j < distance[i]; j++)
        {
            if(j*(times[i]-j) > distance[i]){
            //cout << j*(times[i]-j) << endl;
            winns++;
            }
        }
        combo *= winns;
        winns = 0;
   }
   cout << combo;

}