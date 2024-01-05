#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void getInputFromLine(string in, string& out, vector<int>& nrsOut){
    nrsOut.clear();
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
//returns if it is posible to place a value of size at index
bool canPlaceAt(string inS, int size, int index){ 
    //Fits the string size
    if(inS.length() < (index+size)){
        return false;
    }
    
    //Before is a ? or .
    if(index != 0 && inS[index-1] == '#'){
        return false;
    }
    
    //After is a ? or .
    if(inS[index+size] == '#'){
        return false;
    }
    //inbetween os no .
    for (int i = index; i < (index+size); i++)
    {
        if(inS[i] == '.'){
            return false;
        }
    }
    
    return true;
}

bool canPlaceFirstAt(string inS, int size, int index){
    if(!canPlaceAt(inS,size,index)){
        return false;
    }
    //If there is a # and after you cant place annymore
    for (int i = 0; i < inS.length(); i++)
    {
        if(inS[i] == '#'){
            if(index > i){
                return false;
            }
            return true;
        }
    }
    return true;
}

void findPlaces(string inS, int index, vector<int> numbers,int iNr, int& combo){
    //get the sum of the rest of the numbers + the . between every number
    int sum = numbers.size()-(iNr+1);
    bool notvalid = false;
    for (int i = iNr; i < numbers.size(); i++)
    {
        sum += numbers[i];
    }
    //TODO stop at next #
    for (int i = index; i < inS.length()-(sum-1); i++)
    {
        if(canPlaceAt(inS,numbers[iNr],i)){

            //i this is not the last number continue with the next one
            if(numbers.size()-1 > iNr){
                findPlaces(inS,i+numbers[iNr]+1,numbers,iNr+1,combo);
            }
            //if this is the last number add this as a combo
            if(numbers.size()-1 == iNr){
                notvalid = false;
                //check that last has no # after it
                for (int j = i+numbers[iNr]; j < inS.length(); j++)
                {
                    if(j < inS.length() && inS[j] == '#'){
                        notvalid = true;
                        //cout << j << endl;
                    }
                }
                if(!notvalid){
                    combo++;
                }
            }
            //cout << iNr << " index: " << i+2 << endl;
        }
        if(inS[i] == '#'){
            break;
        }
    }
    
}

int main(){
    fstream input("input.txt");
    string buff;
    
    string code;
    vector<int> numbers;
    int combos = 0;
    
    //getInputFromLine("?.?#.????# 1,2,2",code,numbers);
    //findPlaces(code,0,numbers,0,combos);

    
    int prevcom = combos;
    while (!input.eof())
    {
        getline(input,buff);
        getInputFromLine(buff,code,numbers);
        prevcom = combos;
        findPlaces(code,0,numbers,0,combos);
        //cout << code << " " << combos-prevcom << endl;
    }
    
    
    cout << "Number of ways to set the springs " << combos << endl;
}