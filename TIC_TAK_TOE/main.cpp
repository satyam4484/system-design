
#include<iostream>
#include "Game.cpp"
using namespace std;


int main() {
    int n = 3;
    // cout<<"Enter the board size : ";
    // cin>>n;

    Tic_Tak_Toe game(n);
    game.startGame();
}