#include <iostream>
#include <string>

using namespace std;

// Base class representing the core coffee drink
class Coffee {
public:
    virtual double cost() = 0;
    virtual string description() = 0;
};

// Concrete component representing a basic coffee drink
class SimpleCoffee : public Coffee {
public:
    double cost() override {
        return 2.0;
    }

    string description() override {
        return "Simple coffee";
    }
};

// Decorator class representing an additional option (e.g., milk)
class MilkDecorator : public Coffee {
private:
    Coffee* coffee;

public:
    MilkDecorator(Coffee* c) : coffee(c) {}

    double cost() override {
        return coffee->cost() + 0.5;
    }

    string description() override {
        return coffee->description() + ", with milk";
    }
};

// Decorator class representing another additional option (e.g., sugar)
class SugarDecorator : public Coffee {
private:
    Coffee* coffee;

public:
    SugarDecorator(Coffee* c) : coffee(c) {}

    double cost() override {
        return coffee->cost() + 0.2;
    }

    string description() override {
        return coffee->description() + ", with sugar";
    }
};

// Usage
int main() {
    Coffee* simple_coffee = new SimpleCoffee();
    cout << simple_coffee->description() << endl;  // Output: Simple coffee
    cout << simple_coffee->cost() << endl;         // Output: 2.0

    // Add milk to the coffee
    Coffee* coffee_with_milk = new MilkDecorator(simple_coffee);
    cout << coffee_with_milk->description() << endl;  // Output: Simple coffee, with milk
    cout << coffee_with_milk->cost() << endl;         // Output: 2.5

    // Add sugar to the coffee
    Coffee* coffee_with_sugar = new SugarDecorator(simple_coffee);
    cout << coffee_with_sugar->description() << endl;  // Output: Simple coffee, with sugar
    cout << coffee_with_sugar->cost() << endl;         // Output: 2.2

    delete simple_coffee;
    delete coffee_with_milk;
    delete coffee_with_sugar;

    return 0;
}
