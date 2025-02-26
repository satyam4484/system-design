#pragma once

#include<iostream>
#include<bits/stdc++.h>
#include "Piece.cpp"
using namespace std;


class Player{
    string name;
    string id;
    Piece piece;

    public:
    Player(string name, string id, Piece piece) : name(name), id(id), piece(piece) {}

    string getName() {
        return this->name;
    }

    PieceType getPiece() {
        return this->piece.piecetype;
    }

    string getId() {
        return this->id;
    }
};




