#pragma once
#include "./Vechicle.cpp"
#include "./Ticket.cpp"
#include "./Buldings.cpp"
#include "./Floors.cpp"
#include  "./ParkingSpots.cpp"

class ParkingManager{
    vector<Building*>buildings; // Changed to store pointers
    unordered_map<int,Ticket*> tickets;
    int ticketCounter = 0;
    public:

    ParkingManager() = default;

    void addBuilding(Building* building) { // Changed to accept pointer
        buildings.push_back(building);
    }
    void removeBuilding(int buildingId) {
        buildings.erase(remove_if(buildings.begin(), buildings.end(),
            [buildingId](Building* b) { // Changed to work with pointer
                return b->getBuildingId() == buildingId; // Use -> instead of .
            }), buildings.end());
    }

    ParkingSpot* findAvailableSpot(VehicleType vehicleType) {
        for (auto& building : buildings) {
            ParkingSpot* spot = building->findParkingSpot(vehicleType); // Pass vehicle type
            if (spot != nullptr) {
                return spot; // Return the first available parking spot found
            }
        }
        return nullptr; // No available parking spots in any building
    }

    Ticket* parkVehicle(Vehicle* vehicle) {
        ParkingSpot* spot = findAvailableSpot(vehicle->getType()); // Pass vehicle type
        if (spot == nullptr) {
            throw runtime_error("No available parking spots for this vehicle type.");
        }

        spot->assignVehicle(vehicle);
        Ticket* ticket = new Ticket(++ticketCounter, vehicle, spot);
        tickets[ticketCounter] = ticket;
        return ticket;
    }

    void removeVehicle(int ticketId) {
        auto it = tickets.find(ticketId);
        if (it == tickets.end()) {
            throw runtime_error("Ticket not found.");
        }

        Ticket* ticket = it->second;
        ParkingSpot* spot = ticket->getSpot();
        spot->removeVehicle();
        delete ticket; // Free the ticket memory
        tickets.erase(it); // Remove the ticket from the map
    }
};