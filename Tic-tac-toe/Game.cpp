#include<iostream>
#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include "Board.cpp"
#include "Piece.cpp"

using namespace std;


class TicTacToe{
    public:
    deque<Player>players; // since we need to add player and remove
    Board *gameBoard;
    int size;

    TicTacToe() {}
    
    // initialise the game can be passed dynamic parameters also
    void initializeGame() {
        players.push_back(Player("satyam", PlayingPieceX()));
        players.push_back(Player("abhi", PlayingPieceO()));

        this->gameBoard =new  Board(3);
        this->size =3;
    }

    string StrartGame() {
        bool noWinner = true;

        // run till no winner is found or game is draw
        while(noWinner) {
            
            Player playerturn = players.front();
            players.pop_front();

            // print the board
            gameBoard->PrintBoard();

            // if any freecell exit then move else the game is tie
            int freeCellCount = gameBoard->freeCells;

            if(freeCellCount==0) {
                noWinner = false;
                continue;
            }
            
            // get the user input of row and columns
            cout<<"Player :"<<playerturn.name<<" Enter row,column :";
            auto [row,column] = getUserInput();

            // add piece if possible
            bool addPiece = gameBoard->addPiece(row,column,playerturn.piece->piece);

            // if we are not able to add piece then we have selected the wrong position
            if(!addPiece) {
                cout<<"Incorrect Position chosen , Try again"<<endl;
                players.push_front(playerturn);
                continue;
            }
            // add player back to queue
            players.push_back(playerturn);
            
            // check whether the selected move lets him to win the game 
            bool winner = isThereWinner(row,column,playerturn.piece->piece);
            // if yes then return the player name
            if(winner) {
                return playerturn.name;
            }
            
        }
        return "tie";
    }

    bool isThereWinner(int row,int column,PieceType piece) {
        bool rowMatch = true,colMatch=true,diagonalMatch=true,antiDiagonalMatch = true;

        // check fo that row 
        for(int i=0;i<this->size;i++) {
            // gameBoard->board[row]->at(i).piece  since we accessing 2d vector pointer from another pointer so this syntax is used 
            if(gameBoard->board[row]->at(i).piece == PieceType::N || (gameBoard->board[row]->at(i).piece != piece)) {
                rowMatch = false;
            }
        }
        // check for that column
        for(int i=0;i<this->size;i++) {
            if(gameBoard->board[i]->at(column).piece == PieceType::N || (gameBoard->board[i]->at(column).piece != piece)) {
                colMatch = false;
            }
        }
        // check for that diagonal
        for(int i=0,j=0;i<this->size;i++,j++) {
            if(gameBoard->board[i]->at(j).piece == PieceType::N || gameBoard->board[i]->at(j).piece!=piece) {
                diagonalMatch = false;
            }
        }

        // check for that anti diagonal
        for(int i=0,j=this->size-1;i<this->size;i++,j--) {
            if(gameBoard->board[i]->at(j).piece == PieceType::N || gameBoard->board[i]->at(j).piece!=piece) {
                antiDiagonalMatch = false;
            }
        }

        // player wins if he found any of the positions true
        return rowMatch || colMatch || diagonalMatch || antiDiagonalMatch;
    }

    // this function will basically perform input of string and slicing
    pair<int,int>getUserInput() {
        string s;
        cin>>s;
        istringstream ss(s);
        vector<int>v;

        string token;

        while(getline(ss,token,',')) {
            v.push_back(stoi(token));
        }

        // return the rows and columns
        return {v[0],v[1]};
    }
};