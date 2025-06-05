
#pragma once
#include<iostream>

using namespace std;
enum class VehicleType {
    CAR,
    TRUCK,
    MOTORCYCLE
};

class Vehicle {
protected:
    string vehicleNumber;
public:
    Vehicle(const string& number) : vehicleNumber(number) {}

    virtual VehicleType getType() const = 0;
    virtual string getNumber() const {
        return vehicleNumber;
    }

    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    Car(const string& number) : Vehicle(number) {}

    VehicleType getType() const override {
        return VehicleType::CAR;
    }
    string getNumber() const override {
        return "Car: " + vehicleNumber;
    }
};

class Truck : public Vehicle {
public:
    Truck(const string& number) : Vehicle(number) {}

    VehicleType getType() const override {
        return VehicleType::TRUCK;
    }

    string getNumber() const override {
        return "Truck: " + vehicleNumber;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(const string& number) : Vehicle(number) {}

    VehicleType getType() const override {
        return VehicleType::MOTORCYCLE;
    }

    string getNumber() const override {
        return "Motorcycle: " + vehicleNumber;
    }
};
