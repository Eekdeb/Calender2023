#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

struct RL
{
    string left;
    string right;
};

vector<int> findPrimeFactors(int nr){
    vector<int> factors;
    while (nr%2 == 0)
    {
        nr = nr/2;
        factors.push_back(2);
    }
    for (int i = 3; i < sqrt(nr) ; i++)
    {
        while(nr%i == 0){
            factors.push_back(i);
            nr = nr/i;
        }
    }
    if(nr != 1){
        factors.push_back(nr);
    }
    return factors;
}

void findAndDelet(vector<int>& v, int nr){
    for (int i = 0; i < v.size(); i++)
    {
        if(v[i] == nr){
            v.erase(v.begin() + i);
            return;
        }
    }
}

int main(){
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
    int nrFound = 0;
    int found1 = 0, found2 = 0;
    vector<int> cycles;
	int count = 0, finished;
    //find cyckle time for each seperate string
    for (auto &&place : places)
    {
        while (place[2] != 'Z' || nrFound <= 3)
        {
            if(place[2] == 'Z'){
                //cout << steps << "  " << place << endl;
                if(found1 == 0){
                    found1 = steps;
                }
                else if (found2 == 0){
                    found2 = steps;
                }
                nrFound++;
            }

            if(count > instruktions.length()-1){
                count = 0;
            }
            //cout << instruktions[count] << "  " << steps << "  " << place << " " << count << endl;

            if(instruktions[count] == 'L'){
                place = mRL[place].left;
            }
            if(instruktions[count] == 'R'){
                place = mRL[place].right;
            } 

            steps++;
            count++;
        }
        cycles.push_back(found2 - found1);
        //cout << found2 - found1 << endl;
        found2 = 0;
        found1 = 0;
        nrFound = 0;
        steps = 0;
        count = 0;
    }
    
    //get factors for each cycle
    vector<vector<int>> factors;
    for (int i = 0; i < cycles.size(); i++)
    {
        factors.push_back(findPrimeFactors(cycles[i]));
        /* printinf factors
        for (auto factor : factors[i])
        {
            cout << factor << endl;
        }
        cout << endl;
        */
    }
    
    //take all unique factors multiply them with total
    long long total = 1;
    int temp = 0;
    for (int i = 0; i < cycles.size(); i++)
    {
        while (factors[i].size() != 0)
        {
            temp = factors[i].front();
            total *= temp;
            factors[i].erase(factors[i].begin());
            for (auto &&f : factors)
            {
                findAndDelet(f,temp);
            }
        }
    }

    cout << total;
    return 0;
}

/*

19631*a = 17287*b = 12599*c = 23147*d = 13771*e = 20803*f



*/