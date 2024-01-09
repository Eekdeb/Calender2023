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

void enlarge(string& str, vector<int>& intList){
    string str5;
    int startSize = intList.size();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < startSize; j++)
        {
            intList.push_back(intList[j]);
        }
    }
    str = str + "?" + str + "?" + str + "?" + str + "?" + str;
}

int checkHasAfter(string code, int index){
    bool foundHash = false;
    for (int i = index; i < code.length(); i++)
    {
        if(code[i] == '#'){
            foundHash = true;
        }
    }
    return foundHash;
}

int main(){
    fstream input("input.txt");
    string buff;
    
    string code;
    vector<int> numbers;
    long long totCombo = 0;

    //getInputFromLine("?#????????????##?? 1,1,10",code,numbers);
    //enlarge(code,numbers);

    int iNr = 0;
    long long combo = 0;
    int loopIndexes[50];
    int sums[50];

    for (int i = 0; i < 50; i++)
    {
        loopIndexes[i] = 0;
        sums[i] = 0;
    }
    
    
    //int tcount = 0;
    while (!input.eof())
    //while (tcount == 0)
    {
        //tcount++;
        getline(input,buff);
        getInputFromLine(buff,code,numbers);
        enlarge(code,numbers);
        //getInputFromLine("?.?#?#??.?? 1,3",code,numbers);
        
        for (int i = 0; i < 50; i++)
        {
            loopIndexes[i] = 0;
        }
        iNr = 0;
        combo = 0;

        for(int i = 0; i < numbers.size();i++)
        {
            sums[i] = numbers.size()-(i+1);
            for (int j = i; j < numbers.size(); j++)
            {
                sums[i] += numbers[j];
            }
        }
        
        //end when all solutions are found is when the first can not find a place to be.
        while (iNr >= 0)
        {
            //if you can place it on this pos
            if(canPlaceAt(code,numbers[iNr],loopIndexes[iNr])){
                //if it is not the last one
                if(iNr < numbers.size()-1){
                    loopIndexes[iNr+1] = loopIndexes[iNr]+numbers[iNr]+1;
                    iNr++;
                } else {
                    //is there a # after it?
                    if(!checkHasAfter(code,loopIndexes[iNr]+numbers[iNr])){
                        combo++;
                        //cout << loopIndexes[iNr-1] << loopIndexes[iNr] << endl;
                    }
                    loopIndexes[iNr]++;
                }
                continue;
            }
            //there is no place to put it
            if(loopIndexes[iNr] >= code.length()-(sums[iNr]-1))
                iNr--;
            //it also ends if it is at a #
            if(iNr >= 0){
                int t = loopIndexes[iNr];
                while(code[loopIndexes[iNr]-1] == '#'){
                    iNr--;
                }
            }
            loopIndexes[iNr]++;
            //cout << iNr << " " << loopIndexes[iNr] << endl;
        }
        totCombo += combo;
        cout << combo << endl;
    }
    //7694
    cout << "Number of ways to set the springs " << totCombo << endl;
    input.close();
    return 1;
}