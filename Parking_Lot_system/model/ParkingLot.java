package Parking_Lot_system.model;

import java.util.List;

public class ParkingLot {

    private final String id;
    private final List<Floor> floors;

    public ParkingLot(String id, List<Floor> floors) {
        this.id = id;
        this.floors = floors;
    }

    public String getId() {
        return id;
    }

    public List<Floor> getFloors() {
        return floors;
    }
}
