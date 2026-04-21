package interview.expects;

/**
 * Represents a truck vehicle
 */
public class Truck implements Vehicle {
    private final String licensePlate;
    private final String color;

    public Truck(String licensePlate, String color) {
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
        return VehicleType.TRUCK;
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
        return String.format("Truck{plate='%s', color='%s'}", licensePlate, color);
    }
}
