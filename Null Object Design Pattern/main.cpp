#include<iostream>
#include<bits/stdc++.h>
#include "vehicle.cpp"
#include "vehicleFactory.cpp"

using namespace std;
int main() {

    vehicleFactory *factory = new vehicleFactory(); // create the object of factory 
    vehicleInterface *vehicle = factory->getVechicle("Car"); // find the right object as per the requirement 
    // if not then will get the nullobject instead of nullptr

    cout<<vehicle->getAverage()<<endl;
    cout<<vehicle->getFuelCapacity()<<endl;
    return 0;
}