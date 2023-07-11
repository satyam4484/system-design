#include<bits/stdc++.h>
using namespace std;

#pragma once

class Player{
public:
    string name;
    int currentPosition;
    Player(string name,int currentPosition) {
        this->name = name;
        this->currentPosition = currentPosition;
    }
};
