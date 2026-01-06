package Parking_Lot_system.strategy.allocation;

import java.util.List;
import java.util.Optional;

import Parking_Lot_system.model.ParkingSpot;
import Parking_Lot_system.model.enums.SpotType;
import Parking_Lot_system.model.enums.VehicleType;

public class NearestSpotStrategy implements AllocationStrategy {
        
    @Override
    public Optional<ParkingSpot> findSpot(List<ParkingSpot> spots,VehicleType vehicleType) {

        SpotType requiredSpot = SpotType.fromVehicleType(vehicleType);
        return spots.stream()
        .filter(ParkingSpot::isAvailable)
        .filter(spot -> spot.getType() == requiredSpot)
        .findFirst();
    }

}
