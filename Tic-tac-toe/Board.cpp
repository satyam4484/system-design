#pragma once
#include "Piece.cpp"
#include "Player.cpp"
#include <bits/stdc++.h>
using namespace std;


class Board{
    public:
    int size,freeCells;
    // free cells will count is there any empty cell left in the game
    vector<vector<PlayingPiece>*>board;  // 2d representation of board


    Board(int size) {
        this->size = size;
        for(int i=0;i<size;i++) {
            // initializing the board with N pieces which basicall means place is empty
            this->board.push_back(new vector<PlayingPiece>(size,PieceType::N));
            
        }
        this->freeCells = size*size;
    }

    // adding the piece to the board
    bool addPiece(int row,int column,PlayingPiece piece) {
        if(row >= this->size or column >= this->size) return false;   // if enter row and column is out of the board return 

        // (*board[row])[column].piece -> since we are using pointer so access any element at that we have to refer like that
        // if the board is not equal N means it contains some piece so we cannot place it 
        if((*board[row])[column].piece != PieceType::N) {
            return false;
        }

        // set the piece value
        (*this->board[row])[column] = piece;

        this->freeCells--;
        return true;
    }

    
    // function to print the board
    void PrintBoard() {
        for(int i=0;i<size;i++) {
            for(int j=0;j<size;j++) {
                if((*board[i])[j].piece !=PieceType::N) {
                    // this can be make dynamic by making the hasmap for the index and 
                    cout<<((*board[i])[j].piece ==PieceType::O?"O\t":"X\t");
                }else{
                    cout<<"\t";
                }
                cout<<" | ";
            }
            cout<<endl;
        }
    }
};