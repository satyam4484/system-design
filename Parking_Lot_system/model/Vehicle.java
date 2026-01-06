package Parking_Lot_system.model;
import Parking_Lot_system.model.enums.VehicleType;

public class Vehicle {
    private final String licenseNumber;
    private final VehicleType vehicleType;

    public Vehicle(String licenseNumber, VehicleType vehicleType) {
        this.licenseNumber = licenseNumber;
        this.vehicleType = vehicleType;
    }

    public String getLicenseNumber() {
        return licenseNumber;
    }

    public VehicleType getType() {
        return vehicleType;
    }
}
