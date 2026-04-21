package interview.expects;

/**
 * Standard pricing strategy implementation.
 * 
 * Pricing:
 * - BIKE: $2 per hour
 * - CAR: $5 per hour
 * - TRUCK: $7.5 per hour (1.5x car rate)
 * 
 * Minimum charge: 1 minute = 1/60 of hourly rate
 */
public class StandardPricingStrategy implements PricingStrategy {
    private static final double BIKE_RATE = 2.0;          // $ per hour
    private static final double CAR_RATE = 5.0;           // $ per hour
    private static final double TRUCK_MULTIPLIER = 1.5;   // 1.5x car rate

    @Override
    public double calculateFare(long durationMinutes, VehicleType vehicleType) {
        if (vehicleType == null) {
            throw new IllegalArgumentException("Vehicle type cannot be null");
        }

        if (durationMinutes < 0) {
            throw new IllegalArgumentException("Duration cannot be negative");
        }

        // Minimum charge: 1 minute
        if (durationMinutes == 0) {
            durationMinutes = 1;
        }

        double hourlyRate = getHourlyRate(vehicleType);
        double hours = durationMinutes / 60.0;
        
        return Math.round(hours * hourlyRate * 100.0) / 100.0; // Round to 2 decimal places
    }

    /**
     * Get hourly rate for a vehicle type
     */
    private double getHourlyRate(VehicleType vehicleType) {
        switch (vehicleType) {
            case BIKE:
                return BIKE_RATE;
            case CAR:
                return CAR_RATE;
            case TRUCK:
                return CAR_RATE * TRUCK_MULTIPLIER;
            default:
                throw new IllegalArgumentException("Unknown vehicle type: " + vehicleType);
        }
    }
}
