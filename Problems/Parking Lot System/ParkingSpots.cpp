#pragma once
#include <iostream>
#include "./Vechicle.cpp"

class ParkingSpot {
    int spotId;
    VehicleType spotType;
    bool isOccupied;
    Vehicle* assignedVehicle;

public:
    ParkingSpot(int id, VehicleType type)
        : spotId(id), spotType(type), isOccupied(false), assignedVehicle(nullptr) {}

    int getId() const {
        return spotId;
    }

    VehicleType getType() const {
        return spotType;
    }

    bool isSpotOccupied() const {
        return isOccupied;
    }

    void assignVehicle(Vehicle* vehicle) {
        if (!isOccupied && vehicle->getType() == spotType) {
            assignedVehicle = vehicle;
            isOccupied = true;
        } else {
            throw runtime_error("Error: Spot is occupied or vehicle type mismatch.");
        }
    }

    void removeVehicle() {
        if (isOccupied) {
            assignedVehicle = nullptr;
            isOccupied = false;
        } else {
            throw runtime_error("Error: Spot is already empty.");
        }
    }

    Vehicle* getAssignedVehicle() const {
        return assignedVehicle;
    }

    bool canFitVehicle(const Vehicle* vehicle) const {
        return spotType == vehicle->getType();
    }

    ~ParkingSpot() = default;
};
