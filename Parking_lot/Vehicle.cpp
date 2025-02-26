#include<iostream>
using namespace std;



class VehicleType {
    public:
    string vehicleNumber;
    string vechicleType;
};


class ParkingSpot {
    public:
    int spotNumber;
    bool isOccupied;
    VehicleType vehicle;
};


