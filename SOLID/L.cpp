#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Bike{
    public:
    virtual void turnOnEngine() = 0;
    virtual void accelerate() = 0;
};

class motorcycle:public Bike{
    bool engineOn;
    int speed;
public:
    motorcycle() {
        engineOn = false;
        speed=0;
    }

    void turnOnEngine() {
        engineOn = true;
    }

    void accelerate() {
        speed+=10;
    }
};


// the bicycle class is narrowing down the features of base class so that should not be there
class Bicycle:public Bike{
    int speed;
public:
    Bicycle(){
        speed = 0;
    }

    void turnOnEngine(){
        throw "Bicyle does not have any engine";
    }

    void accelerate() {
        speed+=20;
    }
};


int main() {
    
    return 0;
}