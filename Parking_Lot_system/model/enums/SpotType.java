package Parking_Lot_system.model.enums;

public enum SpotType {
    BIKE,
    COMPACT,
    LARGE;

    public static SpotType fromVehicleType(VehicleType vehicleType) {
        switch (vehicleType) {
            case BIKE:
                return BIKE;
            case CAR:
                return COMPACT;
            case TRUCK:
                return LARGE;
            default:
                throw new IllegalArgumentException("Unknown Vehicle Type: " + vehicleType);
        }
    }
}
