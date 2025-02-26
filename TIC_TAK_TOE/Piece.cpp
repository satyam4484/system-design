#pragma once


#include<iostream>
using namespace std;

enum class PieceType {
    X,
    O,
    _
};

class Piece {
    public:
    PieceType piecetype;

    Piece() = default;
    Piece(PieceType piecetype):piecetype(piecetype) {}
    string getPieceType() {
        if(this->piecetype == PieceType::X) return " X ";
        else if(this->piecetype == PieceType::O) return " O ";
        else return " _ ";
    }
};


class PieceX: public Piece{
    public:
    PieceX(): Piece(PieceType::X) {}
};

class PieceO: public Piece{
    public:
    PieceO(): Piece(PieceType::O) {}
};





