package Problems.Java;

public class Spot {
    private  VehicleType vehicleType;
    boolean isEmpty;

    public Spot() {
        this.isEmpty = true;
    }

    public boolean isSlotEmpty() {
        return isEmpty;
    }

    public void setSlot(boolean slotEmpty) {
        isEmpty = slotEmpty;
    }

    public VehicleType getVehicleType() {
        return vehicleType;
    }

}
