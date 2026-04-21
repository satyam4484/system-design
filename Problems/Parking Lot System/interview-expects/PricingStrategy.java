package interview.expects;

/**
 * Strategy pattern for fare calculation.
 * Allows different pricing strategies to be plugged in.
 * 
 * SOLID Principle: Open/Closed - Open for extension, closed for modification
 */
public interface PricingStrategy {
    /**
     * Calculate fare for a parking session
     * 
     * @param durationMinutes How long the vehicle was parked
     * @param vehicleType Type of vehicle
     * @return Total fare amount in dollars
     */
    double calculateFare(long durationMinutes, VehicleType vehicleType);
}
