package Parking_Lot_system.model;

import java.time.LocalDateTime;

public class Ticket {
    private final String ticketId;
    private final Vehicle vehicle;
    private final ParkingSpot parkingSpot;
    private final LocalDateTime entryTime;
    private LocalDateTime exitTime;

    public Ticket(String ticketId, Vehicle vehicle, ParkingSpot parkingSpot) {
        this.ticketId = ticketId;
        this.vehicle = vehicle;
        this.parkingSpot = parkingSpot;
        this.entryTime = LocalDateTime.now();
    }

    public String getTicketId() {
        return ticketId;
    }

    public Vehicle getVehicle() {
        return vehicle;
    }

    public LocalDateTime getEntryTime() {
        return entryTime;
    }
    
    public ParkingSpot getParkingSpot() {
        return parkingSpot;
    }

    public LocalDateTime getExitTime() {
        return exitTime;
    }

    

    public void markExit() {
        this.exitTime = LocalDateTime.now();
    }
}
