package interview.expects;

/**
 * Represents a single parking spot in the parking lot.
 * Each spot can accommodate only one vehicle of a specific type.
 * 
 * SOLID Principles:
 * - Single Responsibility: Only manages the state of one parking spot
 * - No external dependencies
 */
public class Spot {
    private final int spotId;
    private final int levelId;
    private final VehicleType vehicleType;
    private Vehicle parkedVehicle;
    private boolean isEmpty;

    public Spot(int spotId, int levelId, VehicleType vehicleType) {
        if (vehicleType == null) {
            throw new IllegalArgumentException("Vehicle type cannot be null");
        }
        this.spotId = spotId;
        this.levelId = levelId;
        this.vehicleType = vehicleType;
        this.isEmpty = true;
        this.parkedVehicle = null;
    }

    /**
     * Check if this spot is empty
     */
    public boolean isEmpty() {
        return isEmpty;
    }

    /**
     * Get the vehicle type this spot can accommodate
     */
    public VehicleType getVehicleType() {
        return vehicleType;
    }

    /**
     * Get the currently parked vehicle (null if empty)
     */
    public Vehicle getParkedVehicle() {
        return parkedVehicle;
    }

    /**
     * Park a vehicle in this spot.
     * The vehicle type must match the spot type.
     * 
     * @param vehicle Vehicle to park
     * @return true if successful, false otherwise
     */
    public boolean parkVehicle(Vehicle vehicle) {
        if (vehicle == null) {
            throw new IllegalArgumentException("Vehicle cannot be null");
        }

        // Verify spot is empty
        if (!isEmpty) {
            return false;
        }

        // Verify vehicle type matches spot type
        if (vehicle.getType() != this.vehicleType) {
            return false;
        }

        this.parkedVehicle = vehicle;
        this.isEmpty = false;
        return true;
    }

    /**
     * Unpark the vehicle from this spot
     * 
     * @return The vehicle that was parked, or null if spot was already empty
     */
    public Vehicle unparkVehicle() {
        if (isEmpty) {
            return null;
        }

        Vehicle vehicle = this.parkedVehicle;
        this.parkedVehicle = null;
        this.isEmpty = true;
        return vehicle;
    }

    public int getSpotId() {
        return spotId;
    }

    public int getLevelId() {
        return levelId;
    }

    @Override
    public String toString() {
        return String.format("Spot{id=%d, level=%d, type=%s, empty=%b}",
                spotId, levelId, vehicleType, isEmpty);
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Spot)) return false;
        Spot other = (Spot) obj;
        return this.spotId == other.spotId && this.levelId == other.levelId;
    }

    @Override
    public int hashCode() {
        return 31 * spotId + levelId;
    }
}
