package Problems.Java;

import java.util.ArrayList;

public class ParkingLot {
    private ArrayList<ParkingLevel> levels;

    public ParkingLot(ArrayList<ParkingLevel> levels) {
        this.levels = levels;
    }

    Spot parkVehicle(Vehicle vehicle) {
        // iterate over all the levels
        for(ParkingLevel level : levels){
            Spot spot = level.getParkingSpot(vehicle);
            if(spot.isSlotEmpty()){
                spot.setSlot(false);
                return spot;

            }
        }
       return null;
    }

    boolean unParkVehicle(Spot spot) {
        // iterate over all the levels
        for(ParkingLevel level : levels){
            if(level.parkingSpots.contains(spot)){
                spot.setSlot(true);
                return true;
            }
        }
        return false;
    }
}
