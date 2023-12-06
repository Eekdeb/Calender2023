// C++ program to display "Hello World"
 
// Header file for input output functions
#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief findes and converts the first substring to the desired new string
 * 
 * @param str the main string to look into
 * @param traderThis the subsring that whants to change
 * @param withThis the new string to be inserted
 * @return string: A string with the desired changes
 */
string trader(string str, string traderThis, string withThis){
    int intIndex = 0;
    string out = str;
    for (int i = 0; i < str.length(); i++)
    {
        if(str[i] == traderThis[intIndex])
            intIndex++;
        else if(str[i] == traderThis[0])
            intIndex = 1;
        else
            intIndex = 0;
        if(intIndex == traderThis.length()){
            str.replace(i-traderThis.length()+1,traderThis.length(),withThis);
            intIndex = 0;
            //cout << str;
            //cout << "\n";
        }
    }
    return str;
    
}
 
/**
 * @brief takes a string and finds the first and last number. Putts the first in the 
 * tenth place and the last in the one plase.
 * 
 * @param str the string to inversigate
 * @return int: the first and last number as a number
 */
int decoder(string str){
    int nr1 = 0, nr2 = 0;
    bool firstFound = false;
    for (int i = 0; i < str.length(); i++)
    {
        int currentNr = str[i];
        if(currentNr >= 48 && currentNr <= 57){
            if(!firstFound){
                nr1 = currentNr - 48;
                firstFound = true;
            }
            nr2 =  currentNr - 48;
        }  
    }
    return (nr1*10) + nr2;
}

int main()
{
    string myText2 = "fivebsvvnhgcp6jdqrcfreightwohfh";
    for (size_t i = 0; i < 2; i++)
    {
        //twone threeight sevenine eightwo oneight        
        myText2 = trader(myText2, "twone", "21");
        myText2 = trader(myText2, "threeight", "38");
        myText2 = trader(myText2, "sevenine", "79");
        myText2 = trader(myText2, "oneight", "18");
        myText2 = trader(myText2, "eightwo", "82");
        
        myText2 = trader(myText2, "one", "1");
        myText2 = trader(myText2, "two", "2");
        myText2 = trader(myText2, "three", "3");
        myText2 = trader(myText2, "four", "4");
        myText2 = trader(myText2, "five", "5");
        myText2 = trader(myText2, "six", "6");
        myText2 = trader(myText2, "eight", "8");
        myText2 = trader(myText2, "seven", "7");
        myText2 = trader(myText2, "nine", "9");
    }
    cout << myText2;
    cout << "\n";
    
    
    // Prints hello world
    int nr = 0;
    string myText;

    ifstream InputFile("input.txt");
    int teo;
    int count = 0;
    while(getline(InputFile, myText)) {
        count++;
        for (size_t i = 0; i < 5; i++)
        {
            //twone threeight sevenine eightwo oneight
            myText = trader(myText, "twone", "21");
            myText = trader(myText, "threeight", "38");
            myText = trader(myText, "sevenine", "79");
            myText = trader(myText, "oneight", "18");
            myText = trader(myText, "eightwo", "82");
            
            myText = trader(myText, "three", "3");
            myText = trader(myText, "eight", "8");
            myText = trader(myText, "two", "2");
            myText = trader(myText, "one", "1");
            myText = trader(myText, "four", "4");
            myText = trader(myText, "five", "5");
            myText = trader(myText, "six", "6");
            myText = trader(myText, "seven", "7");
            myText = trader(myText, "nine", "9");
        }
        nr += decoder(myText);
    }
    cout << nr;
    InputFile.close();
    
    return 0;
}