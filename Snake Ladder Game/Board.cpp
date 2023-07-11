#include<bits/stdc++.h>
#include <cstdlib>
#include "Cell.cpp"
#include "Jump.cpp"
using namespace std;


class Board{
    vector<vector<Cell>>cells;
    // Cell[][];
public:
    int boardSize;
    Board(int boardSize,int numberOfSnakes,int numberOfLadders){
        this->boardSize = boardSize;
        initializeCell(boardSize);

        addSnakesLadders(numberOfSnakes,numberOfLadders);
    }

    void initializeCell(int boardSize) {
        cells.resize(boardSize,vector<Cell>(boardSize));
        for(int i=0;i<boardSize;i++) {
            for(int j=0;j<boardSize;j++) {
                Cell cellobj;
                cells[i][j] = cellobj;
            }
        }
        
    }


    void addSnakesLadders(int numberOfSnakes,int numberOfLadders) {
        int lb = 0,ub=boardSize*boardSize;

        // snakes
        while(numberOfSnakes) {
            int snakeHead = rand() % (ub - lb + 1) + lb;
            int snakeTail = rand() % (ub - lb + 1) + lb;

            if(snakeTail >= snakeHead) continue;

            Jump snakeObj;
            snakeObj.start = snakeHead;
            snakeObj.end = snakeTail;

            Cell cell = getCell(snakeHead);
            cell.jump = snakeObj;
            cells[snakeHead/boardSize][snakeHead%boardSize] = cell;
            numberOfSnakes--;

        }

        while(numberOfLadders) {
            int ladderStart = rand() % (ub - lb + 1) + lb;
            int ladderEnd = rand() % (ub - lb + 1) + lb;

            if(ladderStart >= ladderEnd) continue;

            Jump ladderObj;
            ladderObj.start = ladderStart;
            ladderObj.end = ladderEnd;

            Cell cell = getCell(ladderStart);
            cell.jump = ladderObj;
            cells[ladderStart/boardSize][ladderStart%boardSize] = cell;
            numberOfLadders--;
        }
    }


    Cell getCell(int Position){
        int boardRow = Position/(int)cells.size();
        int boardColumn = Position%(int)cells.size();
        return cells[boardRow][boardColumn];
    }
};