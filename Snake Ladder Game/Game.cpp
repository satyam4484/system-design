#pragma once
#include<iostream>
#include<bits/stdc++.h>
#include "Game.cpp"
#include "Board.cpp"
#include "Cell.cpp"
#include "Jump.cpp"
#include "Player.cpp"
#include "Dice.cpp"
#include "Player.cpp"

using namespace std;

class Game{
    Board *board;
    Dice *dice;
    queue<Player*>players;
    Player *winner;
public:
    Game(){
        initializeGame();
    }

    void initializeGame() {
        this->board= new Board(10,5,5);
        this->dice  = new Dice(1);
        this->winner = nullptr;
        addPlayers();
    }

    void addPlayers() {
        Player *p1= new Player("satyam",0);
        Player *p2 = new Player("Abhijeet",0);
        players.push(p1);
        players.push(p2);
    }

    void startGame() {
        while(winner == nullptr) {
            Player *playerTurn=findPlayerTurn();
            cout<<"Player turn is : "<<playerTurn->name<<". Current Position is : "<<playerTurn->currentPosition<<endl;
            

            int diceNumber = dice->rollDice();

            // cout<<"dice number"<<diceNumber<<endl;

            int newPlayerPosition = playerTurn->currentPosition + diceNumber;
            newPlayerPosition = jumpCheck(newPlayerPosition);
            playerTurn->currentPosition=newPlayerPosition;

            int boardSize = this->board->boardSize;
            if(newPlayerPosition >=boardSize*boardSize-1 ) {
                winner = playerTurn;
            }
        }
        cout<<"Winner is : "<<winner->name<<endl;
    }

    Player *findPlayerTurn() {
        Player *playerTurn = players.front();
        players.pop();
        players.push(playerTurn);
        return playerTurn;
    }

    int jumpCheck(int playerPosition) {
        int n = board->boardSize;

        if(playerPosition > n*n-1){
            return playerPosition;
        }

        Cell cell = board->getCell(playerPosition);
        
        if(cell.jump.start!=0 and cell.jump.end!=0 and cell.jump.start == playerPosition) {
            string jumpBy = (cell.jump.start < cell.jump.end)?"Ladder":"Snake";
            cout<<"Jump Done by "<<jumpBy<<endl;
            return cell.jump.end;
        }
        return playerPosition;
    }
};
