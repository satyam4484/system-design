package interview.expects;

/**
 * Represents a bike/motorcycle vehicle
 */
public class Bike implements Vehicle {
    private final String licensePlate;
    private final String color;

    public Bike(String licensePlate, String color) {
        if (licensePlate == null || licensePlate.trim().isEmpty()) {
            throw new IllegalArgumentException("License plate cannot be null or empty");
        }
        if (color == null || color.trim().isEmpty()) {
            throw new IllegalArgumentException("Color cannot be null or empty");
        }
        this.licensePlate = licensePlate;
        this.color = color;
    }

    @Override
    public VehicleType getType() {
        return VehicleType.BIKE;
    }

    @Override
    public String getLicensePlate() {
        return licensePlate;
    }

    @Override
    public String getColor() {
        return color;
    }

    @Override
    public String toString() {
        return String.format("Bike{plate='%s', color='%s'}", licensePlate, color);
    }
}
