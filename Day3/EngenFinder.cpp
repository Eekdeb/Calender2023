#include <iostream>
#include <fstream>
#include <list>
using namespace std;

int addNumbers(string* upperrow, string* midlerow, string* lowerRow);
list<int> findSymbols(string str);
int takeNumber(string* str, int index);

int addNumbers(string* upperrow, string* midlerow, string* lowerRow){
    list<int> symbolIndex = findSymbols(*midlerow);
    int valuesNextToSymbols = 0;
    for (auto i : symbolIndex) {
        //check Upper row
        valuesNextToSymbols += takeNumber(upperrow,i-1);
        valuesNextToSymbols += takeNumber(upperrow,i);
        valuesNextToSymbols += takeNumber(upperrow,i+1);
        //check middle row
        valuesNextToSymbols += takeNumber(midlerow,i-1);
        valuesNextToSymbols += takeNumber(midlerow,i+1);

        //check lower row
        valuesNextToSymbols += takeNumber(lowerRow,i-1);
        valuesNextToSymbols += takeNumber(lowerRow,i);
        valuesNextToSymbols += takeNumber(lowerRow,i+1);
    }
    return valuesNextToSymbols;
}

list<int> findSymbols(string str){
    int symbolPos = 0;
    list<int> symbols{};
    for (int i = 0; i < str.length(); i++)
    {
        //Its a symbol
        if((str[i] < 48 || str[i] > 57) && str[i] != 46){
            symbols.push_back(i);
        }
    }
    return symbols;
}

int takeNumber(string* str, int index){
    //check if current index is a nr
    string p = *str;
    int tmp = p[index];
    int stringLength = p.length();
    int nr = 0;
    if(tmp >= 48 && tmp <= 57){
        int previos = index-1;
        //check if previos nr is int
        while (int(p[previos]) >= 48 && int(p[previos]) <= 57)
        {
            previos--;
            if(previos == -1){
                break;
            }
        }
        previos++;

        int after = index+1;
        //check if after nr is int
        while (int(p[after]) >= 48 && int(p[after]) <= 57)
        {
            after++;
            if(after == stringLength+1){
                break;
            }
        }
        after--;

        int length = after-previos+1;
        for (int i = 0; i < length; i++)
        {
            nr = nr*10 + int(p[previos+i]-48);
            *str = p.replace(previos+i,1,".");
        } 
    }
    return nr;
}

int main()
{
    list<int> symbolIndex{};
    string extra = "............................................................................................................................................";
    string row1,row2,row3;
    int totalValue = 0;
    ifstream InputFile("input.txt");
    getline(InputFile, row1);
    getline(InputFile, row2);
    getline(InputFile, row3);
    //takeNumber(&row2,1);
    totalValue += addNumbers(&row1,&row2,&row3);
    cout << row1 << "\n";
    string next;
    while(getline(InputFile, next)){
        row1 = row2;
        row2 = row3;
        row3 = next;
        totalValue += addNumbers(&row1,&row2,&row3);
        cout << row1 << "\n";
    }

    //last two lines aswell
    row1 = row2;
    row2 = row3;
    row3 = next;
    totalValue += addNumbers(&row1,&row2,&row3);
    cout << row1 << "\n";
    row1 = row2;
    row2 = row3;
    row3 = next;
    totalValue += addNumbers(&row1,&row2,&row3);
    cout << row1 << "\n";
    cout << totalValue << "\n";
}