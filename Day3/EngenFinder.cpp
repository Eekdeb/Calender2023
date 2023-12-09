#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string row1,row2,row3;
    ifstream InputFile("input.txt");
    getline(InputFile, row1);
    getline(InputFile, row2);
    getline(InputFile, row3);
    cout << row2;
}