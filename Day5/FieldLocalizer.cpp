#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<int>> getMatrix(fstream& in){
    vector<vector<int>> matrix;
    vector<int> tempV;
    string nr1s;
    int nr1,nr2,nr3;
    int count = 0;
    while(in >> nr1s)
    {
        if(nr1s.find("to") != string::npos) break;
        nr1 = stoi(nr1s);
        in >> nr2;
        in >> nr3; 
        tempV.push_back(nr1);
        tempV.push_back(nr2);
        tempV.push_back(nr3);
        matrix.push_back(tempV);
        tempV.clear();
    }
    return matrix;
}

int main(){
    
    fstream input ("exampleInput.txt");    
    input.ignore(256,' ');

    vector<int> seeds;
    string buff;
    stringstream buffStream;
    int seed;
    getline(input,buff);
    buffStream.str(buff);
    
    while(!buffStream.eof()){
        buffStream >> seed;
        seeds.push_back(seed);
    }
    input.ignore(256,':');
    input.ignore(256,'\n');

    vector<vector<int>> seedToSoil;
    seedToSoil = getMatrix(input);
    cout << seedToSoil[1][1] << endl;
    input.ignore(256,'\n');

    vector<vector<int>> soilToSome;
    soilToSome = getMatrix(input);
    cout << soilToSome[0][0] << " " << soilToSome[0][1] << " " << soilToSome[0][2] << endl;
    cout << soilToSome[1][0] << " " << soilToSome[1][1] << " " << soilToSome[1][2] << endl;
    cout << soilToSome[2][0] << " " << soilToSome[2][1] << " " << soilToSome[2][2] << endl;

    input.close();
    return 0;
}