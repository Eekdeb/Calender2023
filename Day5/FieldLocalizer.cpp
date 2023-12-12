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
    char name[8];
    int seeds[10];
    int numbers[3];
    fp = fopen("exampleInput.txt","r");
    fscanf(fp, "%s %d %d %d %d", name, &seeds[0],&seeds[1],&seeds[2],&seeds[3]);
    fscanf(fp,"%*s %*s");
    cout << name << "  " << seeds[0] << "  " << seeds[1] << "  " << seeds[2]  << "  " <<seeds[3];


    fscanf(fp,"%d %d %d",&numbers[0],&numbers[1],&numbers[2]);
    cout << "Numbers: " << numbers[0] << "  " << numbers[1] << "  " << numbers[2];

    fclose(fp);
    /*
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
    */
   return 0;
}