#pragma once
#include <bits/stdc++.h>
#include "Piece.cpp"
using namespace std;

// class player that contains the type of piece the player holds
class Player{
    public:
    string name;
    PlayingPiece *piece;
    Player(string name,PlayingPiece piece) {
        this->name = name;
        this->piece = new PlayingPiece(piece);
    }
};