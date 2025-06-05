#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<ctime>
#include "./ParkingManager.cpp"

using namespace std;

int main() {
    // Create a parking lot structure
    cout << "Creating Parking Lot Structure..." << endl;
    
    // Create buildings, floors, and parking spots as pointers
    Building* building1 = new Building(1);
    
    // Create floors for building 1
    Floors* floor1 = new Floors(1);
    Floors* floor2 = new Floors(2);
    
    // Create parking spots for floor 1 - now using pointers
    ParkingSpot* carSpot1 = new ParkingSpot(101, VehicleType::CAR);
    ParkingSpot* carSpot2 = new ParkingSpot(102, VehicleType::CAR);
    ParkingSpot* truckSpot1 = new ParkingSpot(103, VehicleType::TRUCK);
    
    // Create parking spots for floor 2 - now using pointers
    ParkingSpot* carSpot3 = new ParkingSpot(201, VehicleType::CAR);
    ParkingSpot* motorcycleSpot1 = new ParkingSpot(202, VehicleType::MOTORCYCLE);
    
    // Add parking spots to floors - pass pointers
    floor1->addParkingSpot(carSpot1);
    floor1->addParkingSpot(carSpot2);
    floor1->addParkingSpot(truckSpot1);
    
    floor2->addParkingSpot(carSpot3);
    floor2->addParkingSpot(motorcycleSpot1);
    
    // Add floors to building
    building1->addFloor(floor1);
    building1->addFloor(floor2);
    
    // Create parking manager and add building
    ParkingManager parkingManager;
    parkingManager.addBuilding(building1);
    
    cout << "Parking Lot Structure Created Successfully!" << endl;
    cout << "----------------------------------------" << endl;
    
    // Create vehicles
    Car car1("KA-01-HH-1234");
    Car car2("KA-01-HH-5678");
    Truck truck1("KA-01-HH-9012");
    Motorcycle motorcycle1("KA-01-HH-3456");
    
    // Park vehicles
    try {
        cout << "Parking Vehicles..." << endl;
        
        Ticket* ticket1 = parkingManager.parkVehicle(&car1);
        cout << "Ticket issued: " << ticket1->getTicketId() << " for " << car1.getNumber() << endl;
        
        Ticket* ticket2 = parkingManager.parkVehicle(&car2);
        cout << "Ticket issued: " << ticket2->getTicketId() << " for " << car2.getNumber() << endl;
        
        Ticket* ticket3 = parkingManager.parkVehicle(&truck1);
        cout << "Ticket issued: " << ticket3->getTicketId() << " for " << truck1.getNumber() << endl;
        
        // Try to park the motorcycle
        Ticket* ticket4 = parkingManager.parkVehicle(&motorcycle1);
        cout << "Ticket issued: " << ticket4->getTicketId() << " for " << motorcycle1.getNumber() << endl;
        
        cout << "----------------------------------------" << endl;
        
        // Remove a vehicle
        // cout << "Removing Vehicle..." << endl;
        // parkingManager.removeVehicle(1); // Remove the first vehicle
        // cout << "Vehicle with ticket ID 1 removed successfully" << endl;
        
        // Try to park another car after removing one
        Car car3("KA-01-HH-7890");
        Ticket* ticket5 = parkingManager.parkVehicle(&car3);
        cout << "Ticket issued: " << ticket5->getTicketId() << " for " << car3.getNumber() << endl;

        Car car4("KA-09-HH-7890");
        Ticket* ticket6 = parkingManager.parkVehicle(&car4);
        cout << "Ticket issued: " << ticket6->getTicketId() << " for " << car4.getNumber() << endl;
        
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "----------------------------------------" << endl;
    cout << "Parking Lot System Demo Completed!" << endl;
    
    // Clean up allocated memory
    delete carSpot1;
    delete carSpot2;
    delete truckSpot1;
    delete carSpot3;
    delete motorcycleSpot1;
    delete floor1;
    delete floor2;
    delete building1;
    
    return 0;
}