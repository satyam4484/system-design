package Problems.Java;

public class ParkingManager {
    ParkingLot parkingLot;
    TicketManager ticketManager;


    public ParkingManager(ParkingLot parkingLot) {
        this.parkingLot = parkingLot;
    }

    Ticket parkVehicle(Vehicle vehicle) {
        Spot parkingSpot = parkingLot.parkVehicle(vehicle);
        if(parkingSpot == null) {
            System.out.println("Sorry, parking lot is full");
            return null;
        }
        Ticket ticket = ticketManager.getTicket(vehicle,parkingSpot, 0);
        // we will only pass the vehicle
        // it will find the suitable parking spot
        // it will park the vehicle and generate a ticket and return it.
        return ticket;
    }
    public double unParkVehicle(Ticket ticket) {
        // it will go through this parkingticket and unpark the vehicle
        boolean isUnParked = parkingLot.unParkVehicle(ticket.getSpot());
        if(isUnParked) {
            return ticketManager.calculateFare(ticket,0);
        }

        return 0;
    }

    
    
}
