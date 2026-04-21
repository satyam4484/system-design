package interview.expects;

/**
 * Represents an entry or exit gate in the parking lot.
 * Handles vehicle entry and exit operations.
 * 
 * Supports requirement: "Multiple entry and exit points"
 */
public class Gate {
    private final int gateId;
    private final GateType gateType;
    private final ParkingManager parkingManager;

    public Gate(int gateId, GateType gateType, ParkingManager parkingManager) {
        if (gateType == null || parkingManager == null) {
            throw new IllegalArgumentException("Gate type and manager cannot be null");
        }
        this.gateId = gateId;
        this.gateType = gateType;
        this.parkingManager = parkingManager;
    }

    /**
     * Process vehicle entry at this gate
     * 
     * @param vehicle Vehicle entering the parking lot
     * @return Ticket if successful, null if lot is full
     */
    public Ticket processEntry(Vehicle vehicle) {
        if (gateType != GateType.ENTRY) {
            throw new IllegalStateException("Cannot process entry at an EXIT gate");
        }

        if (vehicle == null) {
            throw new IllegalArgumentException("Vehicle cannot be null");
        }

        return parkingManager.parkVehicle(vehicle);
    }

    /**
     * Process vehicle exit at this gate
     * 
     * @param ticket Parking ticket
     * @return Fare amount if successful, 0 if error
     */
    public double processExit(Ticket ticket) {
        if (gateType != GateType.EXIT) {
            throw new IllegalStateException("Cannot process exit at an ENTRY gate");
        }

        if (ticket == null) {
            throw new IllegalArgumentException("Ticket cannot be null");
        }

        return parkingManager.unparkVehicle(ticket);
    }

    public int getGateId() {
        return gateId;
    }

    public GateType getGateType() {
        return gateType;
    }

    @Override
    public String toString() {
        return String.format("Gate{id=%d, type=%s}", gateId, gateType);
    }
}
