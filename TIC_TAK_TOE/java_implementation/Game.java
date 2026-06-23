package TIC_TAK_TOE.java_implementation;

import java.util.List;
import java.util.Scanner;

import TIC_TAK_TOE.java_implementation.enums.GameStatus;

public class Game {
    Board board;
    int GameId;
    GameStatus status;
    int currentUserIndex;
    List<User> users;
    Scanner scanner = new Scanner(System.in);

    Game(int boardSize, List<User> users) {
        this.board = new Board(boardSize);
        this.users = users;
        this.currentUserIndex = 0;
        this.status = GameStatus.IN_PROGRESS;
    }
    boolean checkWinner() {
        return true;
    }

    void startGame() {
        boolean hasGameFinished = false;
        User winnerUser = null;
        while (!hasGameFinished) {
            this.board.displayBoard();

            User currentUser = users.get(currentUserIndex);

            System.out.println(
                    currentUser.getUserName() +
                            "'s turn (" +
                            currentUser.getUserSymbol() +
                            ")");
            int[] input = getUserInput();
            int row = input[0];
            int col = input[1];

            boolean canPlace = this.board.canPlace(row, col);
            if (canPlace) {
                this.board.placeSymbol(row, col, currentUser.getUserSymbol());
                boolean hasWinner = checkWinner();
                if(hasWinner) {
                    System.out.println("We have the winner ");
                    hasGameFinished = true;
                    winnerUser = currentUser;
                }else{
                    this.currentUserIndex = (this.currentUserIndex + 1)%this.users.size();
                }
            } else {
                System.out.print("Invalid Move Please enter Valid moves");
            }

        }

        if(winnerUser != null) {
            System.out.println("Winner is "+ winnerUser.getUserName());
        }
    }

    private int[] getUserInput() {

        System.out.print("Enter row: ");
        int row = scanner.nextInt();

        System.out.print("Enter column: ");
        int column = scanner.nextInt();

        return new int[] { row, column };
    }
}
