#pragma once

#include<bits/stdc++.h>
#include<iostream>
#include "Piece.cpp"
using namespace std;

class Board {
    int boardSize;
    vector<vector<Piece>>*board;
    
    public:
    Board(int boardSize){
        this->boardSize = boardSize;
        this->board = new vector<vector<Piece>>(boardSize,vector<Piece>(boardSize,Piece(PieceType::_)));
    }

    void displayBoard() {
        for(int i=0; i<this->boardSize; i++) {
            for(int j=0; j<this->boardSize; j++) {
                cout << (*this->board)[i][j].getPieceType();
                if (j < this->boardSize - 1) cout << " | ";
            }
            cout << endl;
            if (i < this->boardSize - 1) {
                for(int k=0; k<this->boardSize; k++) {
                    cout << "---";
                    if (k < this->boardSize - 1) cout << "+";
                }
                cout << endl;
            }
        }
    }
    bool hasEmptySlots() {
        for(int i=0;i<this->boardSize; i++) {
            for(int j=0; j<this->boardSize; j++) {
                if((*this->board)[i][j].piecetype == PieceType::_){
                    return true;
                }
            }
        }
        return false;
    }

    bool doWeHaveWinner(PieceType pieceType) {
        // check diagonal has this piece
        bool winner = true;
        for(int i=0;i<this->boardSize;i++) {

            if(this->board->at(i).at(i).piecetype != pieceType) {
                winner = false;
            }
        }
        if(winner) return true;
        
        for(int i=0;i<this->boardSize;i++) {
            if(this->board->at(this->boardSize-i-1).at(i).piecetype != pieceType) {
                winner = false;
            }
        }
        
        for(int i=0;i<this->boardSize;i++) {
            winner = true;
            for(int j=0;j< this->boardSize; j++) {
                if(this->board->at(i).at(j).piecetype != pieceType) {
                    winner = false;
                }
            }
            if(winner) return true;
        }

        for(int i=0;i<this->boardSize;i++) {
            winner = true;
            for(int j=0;j< this->boardSize; j++) {
                if(this->board->at(j).at(i).piecetype != pieceType) {
                    winner = false;
                }
            }
            if(winner) return true;
        }
        return false;
        
    }
    

    bool canAddPiece(int r, int c, PieceType piecetype) {
        if(r>=0 && r<this->boardSize && c>=0 && c<this->boardSize) {
            if((*this->board)[r][c].piecetype == PieceType::_) {
                this->board->at(r).at(c) = Piece(piecetype);
                return true;
            }
        }
        return false;
    }
    
};