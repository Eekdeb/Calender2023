#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

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
    fstream input ("inputNoSpace.txt");
    //fstream input ("exampleInput.txt");
    input.ignore(256,' ');
    string buff;
    
    getline(input,buff);
    long long time = stoll(buff);
    input.ignore(256,':');
    getline(input,buff);
    long long dist = stoll(buff);
    long long pressing,running;
    //find the max time to press the button to get further than dist 
    pressing = -(-time/2) + sqrt((-time/2)*(-time/2)-dist)+1;
    //get the time that it is running
    running = time - pressing;

    long long nrOfCombos = pressing-running+1;
    cout << nrOfCombos << endl;

    /*
    x+y = 55999793 time
    x*y = 401148522741405 dist
    
    x = 55999793 - y
    (55999793 - y)*y = 401148522741405
    55999793y - y^2 = 401148522741405
    0 = y^2 - 55999793y + 401148522741405
    y = -(-55999793)/2 +sqrt((-55999793/2)-401148522741405)

    y = 8433454 or 47566339
    x = 47566339 or 8433454
    x*y =   401148531904906            

    */

}