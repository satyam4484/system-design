package interview.expects;

/**
 * Parking ticket issued to a vehicle when entering the parking lot.
 * Records entry/exit time, spot information, and fare.
 * 
 * Immutable after creation except for exit-related fields.
 */
public class Ticket {
    private final long ticketId;
    private final Vehicle vehicle;
    private final Spot spot;
    private final long entryTime;
    private long exitTime;
    private double fare;

    public Ticket(long ticketId, Vehicle vehicle, Spot spot) {
        if (vehicle == null || spot == null) {
            throw new IllegalArgumentException("Vehicle and spot cannot be null");
        }
        this.ticketId = ticketId;
        this.vehicle = vehicle;
        this.spot = spot;
        this.entryTime = System.currentTimeMillis();
        this.exitTime = 0;
        this.fare = 0;
    }

    /**
     * Mark vehicle as exited and set the fare
     */
    public void exit(double fareAmount) {
        if (fareAmount < 0) {
            throw new IllegalArgumentException("Fare cannot be negative");
        }
        this.exitTime = System.currentTimeMillis();
        this.fare = fareAmount;
    }

    /**
     * Get parking duration in minutes
     */
    public long getDurationMinutes() {
        if (exitTime == 0) {
            return (System.currentTimeMillis() - entryTime) / (1000 * 60);
        }
        return (exitTime - entryTime) / (1000 * 60);
    }

    /**
     * Check if vehicle has exited
     */
    public boolean hasExited() {
        return exitTime > 0;
    }

    // Getters
    public long getTicketId() {
        return ticketId;
    }

    public Vehicle getVehicle() {
        return vehicle;
    }

    public Spot getSpot() {
        return spot;
    }

    public long getEntryTime() {
        return entryTime;
    }

    public long getExitTime() {
        return exitTime;
    }

    public double getFare() {
        return fare;
    }

    @Override
    public String toString() {
        return String.format("Ticket{id=%d, vehicle=%s, duration=%d min, fare=$%.2f}",
                ticketId, vehicle, getDurationMinutes(), fare);
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Ticket)) return false;
        Ticket other = (Ticket) obj;
        return this.ticketId == other.ticketId;
    }

    @Override
    public int hashCode() {
        return (int) (ticketId ^ (ticketId >>> 32));
    }
}
