package interview.expects;

/**
 * Interface representing a vehicle that can be parked in the parking lot.
 * Defines the contract that all vehicle types must follow.
 */
public interface Vehicle {
    /**
     * Get the type of this vehicle
     */
    VehicleType getType();

    /**
     * Get the license plate of the vehicle
     */
    String getLicensePlate();

    /**
     * Get the color of the vehicle
     */
    String getColor();
}
