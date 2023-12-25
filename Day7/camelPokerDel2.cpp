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
    int nrOfCards[14];
    fill(nrOfCards,nrOfCards+14,0);
    int points = 0x0;
    int jokercount = 0;

    //get nr of acurances from each card in hand
    for (auto card : hand)
    {
        int icard = int(card);
        if(icard >= 50 && icard <= 57){
            //index 1-8
            icard -= 49;
        }
        else if (card == 'T'){
            //T == 84 so index 10
            icard -= 74;
        }
        else if (card == 'J'){
            //J == 74 so index 0
            icard -= 74;
            jokercount++;
        }
        else if (card == 'Q'){
            //Q==81 so index 11
            icard -= 70;
        }
        else if (card == 'K'){
            // K==81 so index 12
            icard -= 63;
        }
        else if (card == 'A'){
            // A == 65 so index 13
            icard -= 52;
        }
        nrOfCards[icard]++;
        points = points << 4; 
        points += icard;  
    }

    //dont count joker and add the jokercount to max nr of cards
    nrOfCards[0] = 0;
    int max = 0,maxid;
    for (int i = 0; i < 14; i++)
    {
        if(max <= nrOfCards[i]){
            max = nrOfCards[i];
            maxid = i;
        }
    }
    nrOfCards[maxid] += jokercount;

    //check what thay got for hand
    bool par = false,twoPar = false,tris = false, four = false,five = false,fullhous = false;
    for (int i = 0; i < 14; i++){
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
    
    //give points to the hands
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
    return points;
}

int main(){
    fstream input("input.txt");
    vector<char> hand;
    int bet, points;
    map<int,int> pointHand;
    map<int,vector<char>> test;

    while (!input.eof())
    {
        hand = getHand(input,bet);
        points = getPoints(hand);
        pointHand[points] = bet;
        test[bet] = hand;
    }

    int total = 0;
    int count = 1;
    for(auto it = pointHand.begin();it != pointHand.end();it++){
        total += it->second * count;
        count++;
        /*
        cout << hex << it->first << ":" << dec << it->second << "   \t";
        for (auto c : test[it->second])
        {
            cout << c;
        }
        cout << endl;
        */
    }
    cout << total;
}
