package Problems.Java;

public class Ticket {
    Spot spot;
    Vehicle vehicle;
    long entryTime;
    long exitTime;
    double totalFare;
    public Ticket(Spot spot, Vehicle vehicle, long entryTime) {
        this.spot = spot;
        this.vehicle = vehicle;
        this.entryTime = entryTime;
    }

    Spot getSpot() {
        return spot;
    }

    Vehicle getVehicle() {
        return vehicle;
    }

}
