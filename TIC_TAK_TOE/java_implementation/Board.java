package TIC_TAK_TOE.java_implementation;

import TIC_TAK_TOE.java_implementation.enums.Symbol;

public class Board {
    int boardId;
    int boardSize;
    Cell[][] grid;

    Board(int boardSize) {
        this.boardId = helper.getRandomId();
        this.boardSize = boardSize;
        this.grid = new Cell[boardSize][boardSize];
        initializeBoard();
    }

    private void initializeBoard() {
        for (int i = 0; i < this.boardSize; i++) {
            for (int j = 0; j < this.boardSize; j++) {
                grid[i][j] = new Cell(Symbol.EMPTY);
            }
        }
    }

    boolean canPlace(int row, int column) {
        return this.grid[row][column].isEmpty();
    }

    void placeSymbol(int row, int column, Symbol symbol) {
        this.grid[row][column].setSymbol(symbol);
    }

    void displayBoard() {
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                System.out.print(grid[i][j].getSymbol());
                if (j < boardSize - 1) {
                    System.out.print(" | ");
                }
            }
            System.out.println();
            if (i < boardSize - 1) {
                for (int j = 0; j < boardSize; j++) {
                    System.out.print("---");
                    if (j < boardSize - 1) {
                        System.out.print("+");
                    }
                }
                System.out.println();
            }
        }
    }

}
