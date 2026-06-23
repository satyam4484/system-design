package TIC_TAK_TOE.java_implementation;

import TIC_TAK_TOE.java_implementation.enums.Symbol;

public class User {
    Symbol symbol;
    String name;

    User(Symbol symbol, String name) {
        this.symbol = symbol;
        this.name = name;
    }

    Symbol getUserSymbol(){
        return this.symbol;
    }

    String getUserName() {
        return this.name;
    }
}
