#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#include "Game.cpp"


int main() {
    TicTacToe newgame;
    newgame.initializeGame(); // initializeGame
    cout<<"Game Finished :" <<newgame.StrartGame()<<endl;  // start the game
    return 0;
}