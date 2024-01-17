#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int hashMath(std::string hash){
    int value = 0;
    for (int i = 0; i < hash.length(); i++)
    {
        value += hash[i];
        value *= 17;
        value %= 256;
    }
    return value;
}

int main(){
    std::fstream input("example.txt");
    std::string buff;
    int res = 0, total = 0;
    
    while (!input.eof())
    {
        std::getline(input,buff,',');
        res = hashMath(buff);
        //cout << res << " " << buff << endl;
        total += res;
    }
    //low
    //high 522685
    cout << total << endl;
}