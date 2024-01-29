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

int main(){
    std::vector<LEAF> leafs;
    LEAF start = {0,0,0,0,0,0,0,0};
    start.value = 54;
    leafs.push_back(start);
    start.value = 50;
    leafs.push_back(start);
    std::make_heap(leafs.begin(),leafs.end(),leaf);

    start.value = 500;
    leafs.push_back(start); std::push_heap (leafs.begin(),leafs.end(), leaf);

    for (auto i : leafs)
    {
        std::cout << i.value << " ";
    }
    std::cout << std::endl;
    std::cout << leafs.front().value << std::endl;
}
