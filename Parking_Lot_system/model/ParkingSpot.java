package Parking_Lot_system.model;

import Parking_Lot_system.model.enums.SpotType;

public class ParkingSpot {
    private final String id;
    private final SpotType spotType;
    private boolean isOccupied;

    public ParkingSpot(String id, SpotType spotType) {
        this.id = id;
        this.spotType = spotType;
        this.isOccupied = false;
    }
     public boolean isAvailable() {
        return !isOccupied;
    }

    public void occupySpot() {
        if(isOccupied) {
            throw new IllegalStateException("Parking spot is already occupied.");
        }
        this.isOccupied = true;
    }

    public void vacateSpot() {
        this.isOccupied = false;
    }

    public SpotType getType() {
        return spotType;
    }

    public String getId() {
        return id;
    }
}
