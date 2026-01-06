package Parking_Lot_system.strategy.allocation;

import java.util.List;
import java.util.Optional;

import Parking_Lot_system.model.ParkingSpot;
import Parking_Lot_system.model.enums.VehicleType;

public interface AllocationStrategy {
    Optional<ParkingSpot> findSpot(List<ParkingSpot> spots, VehicleType vehicleType);
}
