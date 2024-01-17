#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <vector>

using namespace std;

struct lense
{
    int focalLength;
    string id;
};


int getBox(string hash){
    int value = 0, length;
    if(hash[hash.length()-1] == '-'){
        length = hash.length()-1;
    }else{
        length = hash.length()-2;
    }
    for (int i = 0; i < length; i++)
    {
        value += hash[i];
        value *= 17;
        value %= 256;
    }
    return value;
}

void setLensInQueue(vector<lense>& lenses, string hash){

    int focalStrength;
    int idIndex;
    string id;
    if(hash[hash.length()-1] == '-'){
        id = hash.substr(0,hash.length()-1);
        focalStrength = -1;
    } else{
        id = hash.substr(0,hash.length()-2);
        focalStrength = hash[hash.length()-1]-48;
    }
    //get if the id is in the list of no
    for (int i = 0; i < lenses.size();i++)
    {
        if(lenses[i].id == id && focalStrength == -1){
            lenses.erase(lenses.begin()+i);
            return;
        }
        if(lenses[i].id == id && focalStrength != -1){
            lenses[i].focalLength = focalStrength;
            return;
        }
    }
    if(focalStrength != -1){
        lense newLens;
        newLens.focalLength = focalStrength;
        newLens.id = id;
        lenses.push_back(newLens);
    }

}

int main(){
    fstream input("input.txt");
    string buff;
    vector<lense> boxes[256];
    int box = 0, total = 0;
    int count = 0;
    cout << getBox("ot=2") << endl;
    while (!input.eof())
    {
        count++;
        getline(input,buff,',');
        box = getBox(buff);
        setLensInQueue(boxes[box],buff);
        //cout << res << " " << buff << endl;
    }

    for (int i = 0; i < 256; i++)
    {
        cout << "Box " << i << endl;
        for(int j = 0; j < boxes[i].size();j++)
        {
            cout << boxes[i][j].id << " " << boxes[i][j].focalLength << endl;
            total += (i+1)*(j+1)*boxes[i][j].focalLength;
        }
    }
    //low
    //high 522685
    cout << total << endl;
}