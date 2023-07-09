#pragma once
#include "Pizza.cpp"


// interface for the toppings
class ToppinDecorator:public BasePizza{};

// concrete class for topping adding extra cheese
class ExtraCheese:public ToppinDecorator{
    BasePizza *pizza;
    public:
    // using constructor injection to inject the pizza
    ExtraCheese(BasePizza *pizza) {
        this->pizza = pizza;
    }

    int cost() {
        return this->pizza->cost() + 15;
    }
};


// toppings
class Mushroom:public ToppinDecorator{
    BasePizza *pizza;
public:
    Mushroom(BasePizza *pizza) {
        this->pizza = pizza;
    }

    int cost() {
        return this->pizza->cost() + 45;
    }
};
