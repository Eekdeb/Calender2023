#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<long long>> getMatrix(fstream& in){
    vector<vector<long long>> matrix;
    vector<long long> tempV;
    string nr1s;
    long long nr1,nr2,nr3;
    int count = 0;
    while(in >> nr1s)
    {
        if(nr1s.find("to") != string::npos) break;
        nr1 = stoll(nr1s);
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

long long getNewValue(long long seed, vector<vector<long long>> sdr){
    for(auto& row : sdr){
        long long source = row[1];
        long long destination = row[0];
        long long range = row[2];
        if(seed >= source && seed < source + range){
            //cout << "source: " << source << " dest: " << destination << " range: " << range << endl;
            return seed - source + destination;
        }
    }
    return seed;
}

int main(){
    
    fstream input ("input.txt");    
    input.ignore(256,' ');

    vector<long long> seeds;
    string buff;
    stringstream buffStream;
    long long seed;
    getline(input,buff);
    buffStream.str(buff);
    
    while(!buffStream.eof()){
        buffStream >> seed;
        seeds.push_back(seed);
    }
    input.ignore(256,':');
    input.ignore(256,'\n');

    vector<vector<long long>> seedToSoil;
    seedToSoil = getMatrix(input);
    input.ignore(256,'\n');

    vector<vector<long long>> soilToFertilizer;
    soilToFertilizer = getMatrix(input);
    input.ignore(256,'\n');

    vector<vector<long long>> fertilizerToWater;
    fertilizerToWater = getMatrix(input);
    input.ignore(256,'\n');

    vector<vector<long long>> waterToLight;
    waterToLight = getMatrix(input);
    input.ignore(256,'\n');

    vector<vector<long long>> lightToTemperature;
    lightToTemperature = getMatrix(input);
    input.ignore(256,'\n');

    vector<vector<long long>> temperatureToHumidity;
    temperatureToHumidity = getMatrix(input);
    input.ignore(256,'\n');

    vector<vector<long long>> humidityToLocation;
    humidityToLocation = getMatrix(input);
    input.ignore(256,'\n');


    long long lowestLocation = 9999999999;
    //change Location
    for (int i = 0; i < seeds.size(); i++)
    {
        seed = seeds[i];
        seed = getNewValue(seed,seedToSoil);
        //cout << seed; << " ";
        seed = getNewValue(seed,soilToFertilizer);
        //cout << seed << " ";
        seed = getNewValue(seed,fertilizerToWater);
        //cout << seed << " ";
        seed = getNewValue(seed,waterToLight);
        //cout << seed << " ";
        seed = getNewValue(seed,lightToTemperature);
        //cout << seed << " ";
        seed = getNewValue(seed,temperatureToHumidity);
        //cout << seed << " ";
        seed = getNewValue(seed,humidityToLocation);
        //cout << seed << endl;  
        if(seed < lowestLocation){
            lowestLocation = seed;
        }  
    }
    cout << "plant at location " << lowestLocation;
    input.close();
    return 0;
}