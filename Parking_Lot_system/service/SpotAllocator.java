package Parking_Lot_system.service;

import java.util.List;

import Parking_Lot_system.exception.NoSpotAvailableException;
import Parking_Lot_system.model.ParkingSpot;
import Parking_Lot_system.model.enums.VehicleType;
import Parking_Lot_system.strategy.allocation.AllocationStrategy;

public class SpotAllocator {
    private final AllocationStrategy allocationStrategy;

    public SpotAllocator(AllocationStrategy allocationStrategy) {
        this.allocationStrategy = allocationStrategy;
    }

    public ParkingSpot allocateSpot(
            List<ParkingSpot> spots,
            VehicleType vehicleType) {
        return allocationStrategy
                .findSpot(spots, vehicleType)
                .orElseThrow(() -> new NoSpotAvailableException(
                        "No parking spot available for vehicle type: " + vehicleType));
    }
}
