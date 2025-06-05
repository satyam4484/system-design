#pragma once

#include<vector>
#include<list>
#include "./ParkingSpots.cpp"

using namespace std;

class Floors {
    int FloorID;
    list<ParkingSpot*> parkingSpots; // Changed to store pointers
    int FilledParkingSpots = 0; 

    public:
        Floors(int id): FloorID(id) {}

        int getFloorId() const {
            return FloorID;
        }
        
        void addParkingSpot(ParkingSpot* spot) { // Changed to accept pointer
            parkingSpots.push_back(spot);
        }

        void removeParkingSpot(int spotId) {
            parkingSpots.remove_if([spotId](ParkingSpot* spot) { // Changed to work with pointer
                return spot->getId() == spotId; // Use -> instead of .
            });
        }

        ParkingSpot* findParkingSpot(VehicleType vehicleType = VehicleType::CAR) {
            // Only check if all spots are filled
            if(FilledParkingSpots >= parkingSpots.size()) {
                return nullptr; // All parking spots are occupied
            }
            
            for (auto& spot : parkingSpots) {
                // Check if spot is not occupied AND can fit the vehicle type
                if (!spot->isSpotOccupied() && spot->getType() == vehicleType) {
                    // Only increment when we find a suitable spot
                    FilledParkingSpots++;
                    return spot;
                }
            }
            return nullptr;
        }
};