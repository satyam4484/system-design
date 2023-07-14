#pragma once
#include "vehicle.cpp"
#include <bits/stdc++.h>
using namespace std;

// using factory design patter to get the object
class vehicleFactory {
public:

    vehicleInterface *getVechicle(string vehicle) {
        if(vehicle =="Car") return new Car();

        // return nullobject instead of nullptr
        return new NullObject();
    }
};