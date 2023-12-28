#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct RL
{
    string left;
    string right;
};

//this takes way to long. The optimised is FindCyckeTime
int maina(){
    fstream input("input.txt");
    string instruktions;
     
    input >> instruktions;
    string from,left,right;
    map<string,RL> mRL;
    vector<string> places;

    
    //get input
    while (!input.eof())
    {
        input >> from;
        input.ignore(4);
        getline(input,left,',');
        input.ignore(1);
        getline(input,right,')');
        mRL[from] = {left,right};
        if(from[2] == 'A'){
            places.push_back(from);
        }
    }

    long long steps = 0;
	int count = 0, finished;
    cout << places.size() << endl;
    while (true)
    {
        if(count > instruktions.length()-1){
            count = 0;
        } 

        finished = 0;
        for (auto place : places){
            if(place[2] == 'Z'){
                finished++;
            }
            if(finished >= 3)
                cout << finished << "  " << steps << endl;
        }
        if(finished == places.size()){
            break;
        } 

        for (auto &&place : places){
            //cout << instruktions[count] << "  " << steps << "  " << place << " " << count << endl;

            if(instruktions[count] == 'L'){
                place = mRL[place].left;
            }
            if(instruktions[count] == 'R'){
                place = mRL[place].right;
            } 
        }

        steps++;
        count++;
    }
	cout << instruktions[count] << " Found " << steps << "  " << places[0] << endl;
	cout << instruktions[count] << " Found " << steps << "  " << places[1] << endl;
	cout << instruktions[count] << " Found " << steps << "  " << places[2] << endl;
	cout << instruktions[count] << " Found " << steps << "  " << places[3] << endl;
    cout << instruktions[count] << " Found " << steps << "  " << places[4] << endl;
	cout << instruktions[count] << " Found " << steps << "  " << places[5] << endl;	
	
    return 0;
}