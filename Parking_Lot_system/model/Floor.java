package Parking_Lot_system.model;

import java.util.List;

public class Floor {

    private final String floorId;
    private final List<ParkingSpot> parkingSpots;

    public Floor(String floorId, List<ParkingSpot> parkingSpots) {
        this.floorId = floorId;
        this.parkingSpots = parkingSpots;
    }

    public String getFloorId() {
        return floorId;
    }

    public List<ParkingSpot> getParkingSpots() {
        return parkingSpots;
    }
}
