#include "./ParkingSpots.cpp"
#include "./Vechicle.cpp"

class Ticket {
    int ticketId;
    Vehicle *vehicle;
    ParkingSpot *spot;
    time_t entryTime;
    public:
    Ticket(int id,Vehicle *v,ParkingSpot *spot): ticketId(id),vehicle(v),spot(spot) {}

    int getTicketId() const { return ticketId; }

    Vehicle* getVehicle() const { return vehicle; }

    ParkingSpot* getSpot() const { return spot; }
    
    time_t getEntryTime() const { return entryTime; }
};