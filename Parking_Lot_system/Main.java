package Parking_Lot_system;

import java.util.List;

import Parking_Lot_system.model.Floor;
import Parking_Lot_system.model.ParkingLot;
import Parking_Lot_system.model.ParkingSpot;
import Parking_Lot_system.model.Ticket;
import Parking_Lot_system.model.Vehicle;
import Parking_Lot_system.model.enums.SpotType;
import Parking_Lot_system.model.enums.VehicleType;
import Parking_Lot_system.service.ParkingLotService;
import Parking_Lot_system.service.SpotAllocator;
import Parking_Lot_system.strategy.allocation.AllocationStrategy;
import Parking_Lot_system.strategy.allocation.NearestSpotStrategy;
import Parking_Lot_system.strategy.payment.CashPaymentStrategy;
import Parking_Lot_system.strategy.payment.PaymentStrategy;
import Parking_Lot_system.strategy.pricing.HourlyPricingStrategy;
import Parking_Lot_system.strategy.pricing.PricingStrategy;

public class Main {
    public static void main(String[] args) {

        // 1. Create parking spots
        ParkingSpot s1 = new ParkingSpot("S1", SpotType.COMPACT);
        ParkingSpot s2 = new ParkingSpot("S2", SpotType.COMPACT);
        ParkingSpot s3 = new ParkingSpot("S3", SpotType.LARGE);

        ParkingSpot s4 = new ParkingSpot("S4", SpotType.COMPACT);
        ParkingSpot s5 = new ParkingSpot("S5", SpotType.LARGE);

        // 2. Create floors
        Floor floor1 = new Floor("F1", List.of(s1, s2, s3));
        Floor floor2 = new Floor("F2", List.of(s4, s5));

        // 3. Create parking lot
        ParkingLot parkingLot = new ParkingLot(
                "PL-1",
                List.of(floor1, floor2)
        );

        // 4. Wire allocation strategy
        AllocationStrategy allocationStrategy = new NearestSpotStrategy();
        SpotAllocator spotAllocator = new SpotAllocator(allocationStrategy);

        // 5. Create parking lot service
        ParkingLotService parkingLotService =
                new ParkingLotService(spotAllocator, parkingLot);

        // 6. Vehicle enters
        Vehicle car = new Vehicle("MH12AB1234", VehicleType.CAR);
        Ticket ticket = parkingLotService.enter(car);

        System.out.println("Vehicle parked at spot: " +
                ticket.getParkingSpot().getId());

        // simulate time passing (optional sleep)
        try {
            Thread.sleep(8000);
        } catch (InterruptedException ignored) {}

        // 7. Exit + pricing + payment
        PricingStrategy pricingStrategy = new HourlyPricingStrategy();
        PaymentStrategy paymentStrategy = new CashPaymentStrategy();

        double fee = parkingLotService.exitAndPay(
                ticket,
                pricingStrategy,
                paymentStrategy
        );

        System.out.println("Parking fee paid: ₹" + fee);
        System.out.println("Spot released: " +
                ticket.getParkingSpot().isAvailable());
    }
}
