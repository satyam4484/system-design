#include<iostream>
#include "Drive.cpp"
#include<bits/stdc++.h>
using namespace std;

class Vehicle{
public:
    DriveInterface *drive;
    Vehicle(DriveInterface *drive) {
        this->drive = drive;
    }
    Vehicle(){}
};

class SportsVehicle:public Vehicle{
public:
    SportsVehicle(DriveInterface *drive):Vehicle(drive){
        cout<<"Sports vehicle"<<endl;
    }
    
};


class PassengerVehicle:public Vehicle{
public:
    PassengerVehicle(DriveInterface *drive):Vehicle(drive){
        cout<<"passenger vehicle"<<endl;
    }
};

int main() {
    NormalDrive nm;  // this can be choose from the user what type of drive they want 
    DriveInterface *drive; // assign the concrete class to drive interface using runtime polymorphism
    drive = &nm;
    SportsVehicle sp(drive);  // pass the type of drive to sports vechicle 
    sp.drive->drive();         // call the drive method 
        
    return 0;
}