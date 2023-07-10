#pragma once

// <<interface>>
class Vehicle{
public:
    virtual int getAverage() = 0;
};

// Types of vehicles
class BMW:public Vehicle{
public:
    int getAverage() {
        return 60;
    }
};

class Mercedes:public Vehicle{
public:
    int getAverage() {
        return 63;
    }
};

class Swift:public Vehicle{
public:
    int getAverage(){
        return 50;
    }
};

class Alto:public Vehicle{
public:
    int getAverage(){
        return 56;
    }
};
