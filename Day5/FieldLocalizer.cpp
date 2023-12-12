#include <iostream>
#include <fstream>
#include <list>
#include <stdio.h>

using namespace std;

int main(){
    
    ifstream InputFile("exampleInput.txt");
    
    FILE *fp;
    /*
    if ((fptr = fopen("exampleInput.txt","rb")) == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }*/
    string name;
    int age;
    fp = fopen("example.txt","r");
    fscanf(fp, "%s %d", name, &age);
    fclose(fp);
    cout << name;

    string lineFromFile;
    //Get seeds
    while(getline(InputFile, lineFromFile)) {
        int a;
        lineFromFile = lineFromFile.substr();
        cout << lineFromFile << "\n";
        if(lineFromFile.length() == 1)
            break;
    }

    while(getline(InputFile, lineFromFile)) {
        cout << lineFromFile << "\n";
        if(lineFromFile.length() == 1)
            break;
    }

}