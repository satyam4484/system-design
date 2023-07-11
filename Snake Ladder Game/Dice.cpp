#pragma once
#include <cstdlib>

class Dice{
    int diceCount;
    int min = 1,max = 6;
public:
    Dice(int diceCount) {
        this->diceCount = diceCount;
    }

    int rollDice(){
        int totalSum = 0;
        int diceUsed = 0;
        while(diceUsed < diceCount) {
            totalSum +=(rand() % max)+1;
            diceUsed++;
        }
        cout<<"Dice"<<totalSum<<endl;
        return totalSum;
    }

};