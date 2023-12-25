#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<map>

#include <bitset>

using namespace std;

vector<char> getHand(fstream& input, int& bet){
    vector<char> hand;
    char card;
    string sbet;
    
    for (int i = 0; i < 5; i++)
    {
        input >> card;
        hand.push_back(card);
    }

    getline(input,sbet);
    bet = stoi(sbet);
    return hand;
}

int getPoints(vector<char> hand){
    int nrOfCards[13];
    fill(nrOfCards,nrOfCards+13,0);
    int points = 0x0;

    //get nr of acurances from each card in hand
    //00000000
    for (auto card : hand)
    {
        int icard = int(card);
        if(icard >= 48 && icard <= 57){
            icard -= 50;
        }
        else if (card == 'T'){
            icard -= 76;
        }
        else if (card == 'J'){
            icard -= 65;
        }
        else if (card == 'Q'){
            icard -= 71;
        }
        else if (card == 'K'){
            icard -= 64;
        }
        else if (card == 'A'){
            icard -= 53;
        }
        nrOfCards[icard]++;
        points = points << 4; 
        points += icard;  
    }

    bool par = false,twoPar = false,tris = false, four = false,five = false,fullhous = false;
    for (int i = 0; i < 13; i++){
        if(nrOfCards[i] == 2 && par){
            twoPar = true;
        }
        else if(nrOfCards[i] == 2){
            par = true;
        }
        if(nrOfCards[i] == 3)
            tris = true;
        if(nrOfCards[i] == 4)
            four = true;
        if(nrOfCards[i] == 5)
            five = true;
    }
    if(par && tris){
        fullhous = true;
    }
    
    if(five){
        points += 0x900000;
    }
    else if(four){
        points += 0x800000;
    }
    else if(fullhous){
        points += 0x700000;
    }
    else if(tris){
        points += 0x600000;
    }
    else if(twoPar){
        points += 0x500000;
    }
    else if(par){
        points += 0x400000;
    }
    //cout << hex << points << endl;   
    //cout << dec;  
    //cout << endl;
    return points;
}

int main(){
    fstream input("input.txt");
    vector<char> hand;
    int bet, points;
    map<int,int> pointHand;

    while (!input.eof())
    {
        hand = getHand(input,bet);
        points = getPoints(hand);
        pointHand[points] = bet;
    }

    int total = 0;
    int count = 1;
    for(auto it = pointHand.begin();it != pointHand.end();it++){
        total += it->second * count;
        count++;
        cout << hex << it->first << ":" << dec << it->second << endl;
    }
    cout << total;
}
