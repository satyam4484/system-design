#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class BaseCoffee{
    public:
        virtual string getDescription() = 0;
        virtual double cost()  = 0;
        virtual ~BaseCoffee() = default;
};

class simpleCoffee: public BaseCoffee{
    private:
    int price;
    public:
        simpleCoffee(int price): price(price){};
        string getDescription() override{
            return "Simple Coffee";
        }

        double cost() override{
            return this->price;
        }
};

class CoffeeDecorator : public BaseCoffee {
protected:
public:
    virtual string getDescription() override = 0;
    virtual double cost() override = 0;
};

class milk: public BaseCoffee{
    private:
    BaseCoffee *coffee;
    int price;
    public:
        milk(BaseCoffee *coffee, int price): coffee(coffee), price(price){};

        string getDescription() override{
            return coffee->getDescription() + " + Milk";
        }
        double cost() override{
            return coffee->cost() + this->price;
        }
};

class Sugar:  public BaseCoffee{
    private:
    BaseCoffee *coffee;
    int price;
    public:
        Sugar(BaseCoffee *coffee, int price): coffee(coffee), price(price){};

        string getDescription() override{
            return coffee->getDescription() + " + Sugar";
        }

        double cost() override{
            return coffee->cost() + this->price;
        }
};


class whippedCream: public BaseCoffee{
    int price;
    BaseCoffee *coffee;

    public:
        whippedCream(BaseCoffee *coffee, int price) : coffee(coffee), price(price) {};

        string getDescription() override {
            return this->coffee->getDescription()+ " + WhippedCream";
        }

        double cost() override {
            return this->coffee->cost() + this->price;

        }
};

int main(){

    BaseCoffee *coffee = new simpleCoffee(10);
    cout << coffee->getDescription() << " " << coffee->cost() << endl;

    coffee = new milk(coffee, 5);
    cout << coffee->getDescription() << " " << coffee->cost() << endl;

    coffee = new Sugar(coffee,15);
    cout << coffee->getDescription() << " " << coffee->cost() << endl;

    coffee = new whippedCream(coffee, 25);
    cout << coffee->getDescription() << " " << coffee->cost() << endl;
    return 0;
}