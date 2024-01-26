#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

//using namespace std;

struct LEAF
{
    int row;
    int col;
    int value;
    int uppCount;
    int rightCount;
    int downCount;
    int leftCount;
    int nrOfSteps;
    bool operator() (LEAF i,LEAF j) { return (i.value<j.value);}
} leaf;

bool stepsSort(LEAF i, LEAF j) {return (i.nrOfSteps < j.nrOfSteps);}


int main(){

    std::vector<LEAF> leafs;
    LEAF test = {0,0,10,0,0,0,20};
    
    leafs.push_back(test);
    test.value = 20;
    test.nrOfSteps = 10;
    leafs.push_back(test);

    test.value = 12;
    test.nrOfSteps = 3;
    auto lower = std::lower_bound(leafs.begin(), leafs.end(), test,leaf);
    int index = std::distance(leafs.begin(), lower);
    leafs.insert(leafs.begin()+index,test);


    for (auto i : leafs)
    {
        std::cout << i.value << " ";
    }
    std::cout << std::endl;
    std::sort(leafs.begin(),leafs.end(),stepsSort);

    for (auto i : leafs)
    {
        std::cout << i.nrOfSteps << " ";
    }
    
}
