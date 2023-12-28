#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

struct RL
{
    string left;
    string right;
};


int main(){
    //fstream input("input.txt");
    fstream input("ruudIn.txt");
    string instruktions;
     
    input >> instruktions;
    string from,left,right;
    map<string,RL> mRL;
    
    //get input
    while (!input.eof())
    {
        input >> from;
        input.ignore(4);
        getline(input,left,',');
        input.ignore(1);
        getline(input,right,')');
        mRL[from] = {left,right};
    }

    
    string place = "AAA";
    int steps = 0;
	int count = 0;
    
    while (place != "ZZZ")
    {
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
	cout << instruktions[count] << " Found " << steps << "  " << place << endl;

	
	
    return 0;
}