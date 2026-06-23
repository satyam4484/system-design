package TIC_TAK_TOE.java_implementation;

public class Move {
    int moveId;
    int row;
    int column;
    User user;

    Move(int row,int column, User user) {
        this.row = row;
        this.column = column;
        this.user = user;
        this.moveId = helper.getRandomId();
    }
}
