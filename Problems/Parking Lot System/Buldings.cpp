#pragma once
#include<vector>
#include<list>
#include "./Floors.cpp"
using namespace std;

class Building{
    int buildingID;
    list<Floors*>floors; // Changed to store pointers
    public:
        Building(int id): buildingID(id) {}
        int getBuildingId() const {
            return buildingID;
        }

        void addFloor(Floors* floor) { // Changed to accept pointer
            floors.push_back(floor);
        }
        void removeFloor(int floorId) {
            floors.remove_if([floorId](Floors* floor) { // Changed to work with pointer
                return floor->getFloorId() == floorId; // Use -> instead of .
            });
        }

        ParkingSpot* findParkingSpot(VehicleType vehicleType = VehicleType::CAR) {
            for (auto& floor : floors) {
                ParkingSpot* spot = floor->findParkingSpot(vehicleType); // Pass vehicle type
                if (spot != nullptr) {
                    return spot; // Return the first available parking spot found
                }
            }
            return nullptr; // No available parking spots in any floor
        }
};