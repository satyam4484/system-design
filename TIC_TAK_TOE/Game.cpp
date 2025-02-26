#pragma once
#include<bits/stdc++.h>
#include<iostream>

#include "Board.cpp"
#include "Piece.cpp"
#include "Player.cpp"

using namespace std;


class Tic_Tak_Toe{
    Board board;
    deque<Player>players;

    public:
    Tic_Tak_Toe(int boardSize): board(boardSize) {
        initializeGame();
    }

    void initializeGame() {
        // cout<<"Enter the number of players: ";
        // int n;
        // cin>>n;
        this->players.push_back(Player("Player 1", "1", Piece(PieceType::X)));
        this->players.push_back(Player("Player 2", "2", Piece(PieceType::O)));
        // for(int i=0; i<n; i++) {
        //     string name;
        //     cout<<"Enter the name of player "<<i+1<<": ";
        //     cin>>name;
        //     cout<<"Select the piece for player "<<i+1<<": ";
        //     cout<<"1. X"<<endl;
        //     cout<<"2. O"<<endl; 
        //     int choice;
        //     cin>>choice;
        //     Piece piece = (choice == 1) ? PieceType::X : PieceType::O;
        //     players.push_back(Player(name, to_string(i+1), piece));
        // }
    }

    

    void startGame() {
        while(true) {

            if(this->board.hasEmptySlots()  == false) {
                cout<<"Match is tied. Thank you for playing ";
                break;
            }
            
            Player playerTurn = this->players.front();
            this->players.pop_front();
            cout<<playerTurn.getName()<<"'s turn"<<endl;

            this->board.displayBoard();
            
            cout<<"Enter the row and column to place the piece: ";
            int r, c;
            cin>>r>>c;

            // check if there are empty slots or not.
            

            if(this->board.canAddPiece(r,c,playerTurn.getPiece())) {
                bool hasWinner = this->board.doWeHaveWinner(playerTurn.getPiece());
                this->players.push_back(playerTurn);

                if(hasWinner){
                    cout<<"Congratulation : "<<playerTurn.getName()<<" Won the match.";
                    this->board.displayBoard();
                    break;             
                }
            }else{
                cout<<"Invalid move Please Try again !!!"<<endl;
                this->players.push_front(playerTurn);
            }
        }
    }

};
