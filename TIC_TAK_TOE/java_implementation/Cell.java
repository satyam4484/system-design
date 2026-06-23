package TIC_TAK_TOE.java_implementation;
import TIC_TAK_TOE.java_implementation.enums.Symbol;


public class Cell {
    Symbol symbol;
    int cellId;

    Cell(Symbol symbol){
        this.symbol = symbol;
    }

    public String getSymbol(){
        return this.symbol.toString();
    }

    boolean isEmpty(){
        return this.symbol == Symbol.EMPTY;
    }

    public void setSymbol(Symbol symbol) {
        this.symbol = symbol;
    }

}
