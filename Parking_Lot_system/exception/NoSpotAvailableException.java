package Parking_Lot_system.exception;

public class NoSpotAvailableException extends RuntimeException {

    public NoSpotAvailableException(String message) {
        super(message);
    }
}
