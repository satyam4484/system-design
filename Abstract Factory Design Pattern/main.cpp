#include<iostream>
#include<bits/stdc++.h>
#include "Vehicle.cpp"

using namespace std;

// abstract vehicle interface
class VehicleFactory{
    public:
    virtual Vehicle *getVehicle(string vehicle) = 0;
};


// factory to decide the type of vehicle
class LuxuryVehicle:public VehicleFactory{
public:
    Vehicle *getVehicle(string vehicle){
        if(vehicle == "BMW") return new BMW();
        else if(vehicle =="Mercedes") return new Mercedes();
        return nullptr;
    }
};

class OrdinaryVehicle:public VehicleFactory{
public:
    Vehicle *getVehicle(string vehicle) {
        if(vehicle == "Swift") return new Swift();
        else if(vehicle =="Alto") return new Alto();
        return nullptr;
    }
};


int main() {

    
    VehicleFactory *vehicle = new OrdinaryVehicle();
    cout<<vehicle->getVehicle("Swift")->getAverage()<<endl;
    
    return 0;
}