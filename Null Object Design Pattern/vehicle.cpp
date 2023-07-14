#pragma once
#include <bits/stdc++.h>

// vehicle interface
class vehicleInterface {
public:
    virtual int getFuelCapacity() = 0;
    virtual int getAverage() = 0;
};  

// concrete real class
class Car:public vehicleInterface{
public:
    int getFuelCapacity() {return 50;}
    int getAverage() {return 60;}
};

// concrete null class
class NullObject:public vehicleInterface{
public:
    int getFuelCapacity() {return 0;}

    int getAverage() {return 0;}
};

