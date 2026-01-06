package Parking_Lot_system.service;

import java.util.UUID;

import Parking_Lot_system.exception.NoSpotAvailableException;
import Parking_Lot_system.exception.PaymentFailedException;
import Parking_Lot_system.model.Floor;
import Parking_Lot_system.model.ParkingLot;
import Parking_Lot_system.model.ParkingSpot;
import Parking_Lot_system.model.Ticket;
import Parking_Lot_system.model.Vehicle;
import Parking_Lot_system.strategy.payment.PaymentStrategy;
import Parking_Lot_system.strategy.pricing.PricingStrategy;

public class ParkingLotService {
    private final SpotAllocator spotAllocator;
    private final ParkingLot parkingLot;

    public ParkingLotService(
            SpotAllocator spotAllocator,
            ParkingLot parkingLot) {
        this.spotAllocator = spotAllocator;
        this.parkingLot = parkingLot;
    }

    public Ticket enter(Vehicle vehicle) {

        for (Floor floor : parkingLot.getFloors()) {
            try {
                ParkingSpot spot = spotAllocator.allocateSpot(
                        floor.getParkingSpots(),
                        vehicle.getType());

                Ticket ticket = new Ticket(
                        UUID.randomUUID().toString(),
                        vehicle,
                        spot);

                spot.occupySpot();
                return ticket;

            } catch (NoSpotAvailableException ignored) {
                // try next floor
            }
        }

        throw new NoSpotAvailableException(
                "Parking lot full for vehicle type: " + vehicle.getType());
    }

    public double exit(Ticket ticket, PricingStrategy pricingStrategy) {

        // 1. Mark exit time
        ticket.markExit();

        // 2. Calculate fee
        double fee = pricingStrategy.calculateFee(ticket);

        // 3. Release spot
        ticket.getParkingSpot().vacateSpot();

        return fee;
    }

    public double exitAndPay(
            Ticket ticket,
            PricingStrategy pricingStrategy,
            PaymentStrategy paymentStrategy) {
        // 1. mark exit
        ticket.markExit();

        // 2. calculate fee
        double fee = pricingStrategy.calculateFee(ticket);

        // 3. process payment
        boolean paymentSuccess = paymentStrategy.pay(fee);
        if (!paymentSuccess) {
            throw new PaymentFailedException("Payment failed. Exit denied.");
        }

        // 4. release spot ONLY after successful payment
        ticket.getParkingSpot().vacateSpot();

        return fee;
    }
}
