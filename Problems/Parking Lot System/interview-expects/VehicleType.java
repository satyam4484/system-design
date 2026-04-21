package interview.expects;

/**
 * Enum representing different types of vehicles that can be parked
 */
public enum VehicleType {
    CAR(1),
    BIKE(0.5),
    TRUCK(2);

    private final double spaceMultiplier;

    VehicleType(double spaceMultiplier) {
        this.spaceMultiplier = spaceMultiplier;
    }

    public double getSpaceMultiplier() {
        return spaceMultiplier;
    }
}
