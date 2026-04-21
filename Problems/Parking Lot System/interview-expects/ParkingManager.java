package interview.expects;

/**
 * Main parking management service.
 * Orchestrates parking lot operations and ticket management.
 * 
 * SOLID Principles:
 * - Single Responsibility: Manages parking operations
 * - Dependency Inversion: Depends on abstractions (ParkingLot, TicketManager)
 * - Thread Safe: Delegates to thread-safe components
 */
public class ParkingManager {
    private final ParkingLot parkingLot;
    private final TicketManager ticketManager;

    public ParkingManager(ParkingLot parkingLot, TicketManager ticketManager) {
        if (parkingLot == null || ticketManager == null) {
            throw new IllegalArgumentException("ParkingLot and TicketManager cannot be null");
        }
        this.parkingLot = parkingLot;
        this.ticketManager = ticketManager;
    }

    /**
     * Park a vehicle in the lot.
     * 
     * @param vehicle Vehicle to park
     * @return Ticket if successful, null if no spot available
     * @throws IllegalArgumentException if vehicle is null
     */
    public Ticket parkVehicle(Vehicle vehicle) {
        if (vehicle == null) {
            throw new IllegalArgumentException("Vehicle cannot be null");
        }

        // Check availability first
        if (!parkingLot.hasAvailableSpot(vehicle.getType())) {
            return null; // No spot available
        }

        // Find and park the vehicle
        Spot spot = parkingLot.parkVehicle(vehicle);

        if (spot == null) {
            return null; // Parking failed
        }

        // Generate and return ticket
        return ticketManager.generateTicket(vehicle, spot);
    }

    /**
     * Unpark a vehicle and calculate fare.
     * 
     * @param ticket The parking ticket
     * @return Fare amount to be paid
     * @throws IllegalArgumentException if ticket is null
     */
    public double unparkVehicle(Ticket ticket) {
        if (ticket == null) {
            throw new IllegalArgumentException("Ticket cannot be null");
        }

        if (ticket.hasExited()) {
            throw new IllegalStateException("Vehicle has already exited");
        }

        Spot spot = ticket.getSpot();

        // Unpark from the lot
        Vehicle unparkedVehicle = parkingLot.unparkVehicle(spot);

        if (unparkedVehicle == null) {
            throw new IllegalStateException("Vehicle not found at spot");
        }

        // Calculate fare
        return ticketManager.calculateFare(ticket);
    }

    /**
     * Get real-time parking availability
     * 
     * @return Information about available spots
     */
    public void displayAvailability() {
        System.out.println("\n=== PARKING LOT STATUS ===");
        System.out.printf("Overall Occupancy: %.1f%%\n", parkingLot.getOccupancyPercentage());
        System.out.println("Available Spots:");

        for (VehicleType type : VehicleType.values()) {
            int available = parkingLot.getAvailableSpots().getOrDefault(type, 0);
            int total = parkingLot.getTotalSpots(type);
            System.out.printf("  %-8s: %2d / %2d\n", type, available, total);
        }
        System.out.println("========================\n");
    }

    /**
     * Check if parking lot has available spots
     */
    public boolean hasAvailableSpots() {
        return !parkingLot.isFull();
    }

    public ParkingLot getParkingLot() {
        return parkingLot;
    }

    public TicketManager getTicketManager() {
        return ticketManager;
    }
}
