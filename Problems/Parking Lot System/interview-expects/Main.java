package interview.expects;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * Complete demonstration of the Parking Lot System.
 * Shows all features matching interview expectations.
 * 
 * Features Demonstrated:
 * 1. Multiple levels with type-specific spots
 * 2. Vehicle parking and unparking
 * 3. Type matching (car spots != bike spots)
 * 4. Real-time availability tracking
 * 5. Thread-safe concurrent access
 * 6. Multiple entry and exit gates
 * 7. Fare calculation with different pricing
 * 8. Error handling and validation
 */
public class Main {
    
    public static void main(String[] args) throws InterruptedException {
        printHeader("PARKING LOT SYSTEM - COMPLETE DEMONSTRATION");
        
        // Setup parking lot
        ParkingLot parkingLot = setupParkingLot();
        TicketManager ticketManager = new TicketManager(new StandardPricingStrategy());
        ParkingManager parkingManager = new ParkingManager(parkingLot, ticketManager);
        
        System.out.println("\n✓ Parking Lot initialized successfully");
        parkingManager.displayAvailability();
        
        // Demo 1: Basic parking operations
        demo1_BasicOperations(parkingManager);
        
        // Demo 2: Type-specific parking (core requirement)
        demo2_TypeSpecificParking(parkingManager);
        
        // Demo 3: Multiple entry/exit gates
        demo3_MultipleGates(parkingManager);
        
        // Demo 4: Concurrent access (thread safety)
        demo4_ConcurrentAccess(parkingManager);
        
        // Demo 5: Real-time availability
        demo5_Availability(parkingManager);
        
        // Demo 6: Edge cases and error handling
        demo6_EdgeCases(parkingManager);
        
        printHeader("ALL DEMOS COMPLETED SUCCESSFULLY ✓");
    }

    /**
     * Setup parking lot with levels and spots
     */
    private static ParkingLot setupParkingLot() {
        List<ParkingLevel> levels = new ArrayList<>();
        
        // Level 1: 5 CAR spots, 3 BIKE spots, 2 TRUCK spots
        List<Spot> level1Spots = new ArrayList<>();
        for (int i = 1; i <= 5; i++) {
            level1Spots.add(new Spot(i, 0, VehicleType.CAR));
        }
        for (int i = 6; i <= 8; i++) {
            level1Spots.add(new Spot(i, 0, VehicleType.BIKE));
        }
        for (int i = 9; i <= 10; i++) {
            level1Spots.add(new Spot(i, 0, VehicleType.TRUCK));
        }
        levels.add(new ParkingLevel(1, level1Spots));
        
        // Level 2: 4 CAR spots, 2 BIKE spots
        List<Spot> level2Spots = new ArrayList<>();
        for (int i = 1; i <= 4; i++) {
            level2Spots.add(new Spot(i, 1, VehicleType.CAR));
        }
        for (int i = 5; i <= 6; i++) {
            level2Spots.add(new Spot(i, 1, VehicleType.BIKE));
        }
        levels.add(new ParkingLevel(2, level2Spots));
        
        return new ParkingLot(1, levels);
    }

    /**
     * Demo 1: Basic parking and unparking
     */
    private static void demo1_BasicOperations(ParkingManager manager) {
        printSection("DEMO 1: Basic Parking/Unparking Operations");
        
        // Park a car
        System.out.println("\n→ Parking a car (ABC-100, RED)");
        Vehicle car1 = new Car("ABC-100", "RED");
        Ticket ticket1 = manager.parkVehicle(car1);
        
        if (ticket1 != null) {
            System.out.println("✓ Car parked successfully - Ticket: " + ticket1.getTicketId());
        }
        
        // Park a bike
        System.out.println("\n→ Parking a bike (BIKE-200, BLUE)");
        Vehicle bike1 = new Bike("BIKE-200", "BLUE");
        Ticket ticket2 = manager.parkVehicle(bike1);
        
        if (ticket2 != null) {
            System.out.println("✓ Bike parked successfully - Ticket: " + ticket2.getTicketId());
        }
        
        // Simulate parking time
        try { Thread.sleep(500); } catch (InterruptedException e) {}
        
        // Unpark
        System.out.println("\n→ Unparking car...");
        double fare1 = manager.unparkVehicle(ticket1);
        System.out.printf("✓ Car unparked - Fare: $%.2f\n", fare1);
        
        System.out.println("\n→ Unparking bike...");
        double fare2 = manager.unparkVehicle(ticket2);
        System.out.printf("✓ Bike unparked - Fare: $%.2f\n", fare2);
        
        manager.displayAvailability();
    }

    /**
     * Demo 2: Type-specific parking (validates core requirement)
     */
    private static void demo2_TypeSpecificParking(ParkingManager manager) {
        printSection("DEMO 2: Type-Specific Parking (Core Requirement)");
        
        System.out.println("\n→ Attempting to park cars in CAR-only spots");
        List<Ticket> tickets = new ArrayList<>();
        
        for (int i = 0; i < 5; i++) {
            Vehicle car = new Car("CAR-" + (300 + i), "COLOR-" + i);
            Ticket ticket = manager.parkVehicle(car);
            if (ticket != null) {
                System.out.println("  ✓ Car " + (i + 1) + " parked - Ticket: " + ticket.getTicketId());
                tickets.add(ticket);
            } else {
                System.out.println("  ✗ Car " + (i + 1) + " - No CAR spot available");
            }
        }
        
        System.out.println("\n→ Attempting to park 6th car (should fail)");
        Vehicle car6 = new Car("CAR-305", "WHITE");
        Ticket ticket6 = manager.parkVehicle(car6);
        if (ticket6 == null) {
            System.out.println("  ✓ Correctly rejected - No CAR spots available");
        }
        
        System.out.println("\n→ But BIKE spots should still be available");
        Vehicle bike = new Bike("BIKE-400", "GREEN");
        Ticket bikeTicket = manager.parkVehicle(bike);
        if (bikeTicket != null) {
            System.out.println("  ✓ Bike parked successfully - Different spot type");
            tickets.add(bikeTicket);
        }
        
        manager.displayAvailability();
        
        // Cleanup
        System.out.println("\n→ Unpacking all vehicles...");
        for (Ticket t : tickets) {
            manager.unparkVehicle(t);
        }
    }

    /**
     * Demo 3: Multiple entry and exit gates
     */
    private static void demo3_MultipleGates(ParkingManager manager) {
        printSection("DEMO 3: Multiple Entry/Exit Points");
        
        // Create multiple gates
        Gate entryGate1 = new Gate(1, GateType.ENTRY, manager);
        Gate entryGate2 = new Gate(2, GateType.ENTRY, manager);
        Gate exitGate1 = new Gate(1, GateType.EXIT, manager);
        Gate exitGate2 = new Gate(2, GateType.EXIT, manager);
        
        System.out.println("\n✓ Created 2 entry gates and 2 exit gates");
        
        // Vehicles entering from different gates
        System.out.println("\n→ Vehicles entering from different gates:");
        Vehicle car1 = new Car("GATE-101", "RED");
        Ticket t1 = entryGate1.processEntry(car1);
        if (t1 != null) {
            System.out.println("  ✓ Car entered via Gate 1 - Ticket: " + t1.getTicketId());
        }
        
        Vehicle car2 = new Car("GATE-102", "BLUE");
        Ticket t2 = entryGate2.processEntry(car2);
        if (t2 != null) {
            System.out.println("  ✓ Car entered via Gate 2 - Ticket: " + t2.getTicketId());
        }
        
        // Vehicles exiting from different gates
        System.out.println("\n→ Vehicles exiting from different gates:");
        double fare1 = exitGate1.processExit(t1);
        System.out.printf("  ✓ Car exited via Gate 1 - Fare: $%.2f\n", fare1);
        
        double fare2 = exitGate2.processExit(t2);
        System.out.printf("  ✓ Car exited via Gate 2 - Fare: $%.2f\n", fare2);
    }

    /**
     * Demo 4: Concurrent access with thread safety
     */
    private static void demo4_ConcurrentAccess(ParkingManager manager) throws InterruptedException {
        printSection("DEMO 4: Thread Safety & Concurrent Access");
        
        System.out.println("\n→ Launching 20 threads trying to park simultaneously");
        System.out.println("→ This demonstrates thread-safe locking mechanisms");
        
        ExecutorService executor = Executors.newFixedThreadPool(10);
        List<Ticket> tickets = new ArrayList<>();
        
        for (int i = 0; i < 20; i++) {
            final int index = i;
            executor.execute(() -> {
                try {
                    // Odd threads park cars, even threads park bikes
                    Vehicle vehicle;
                    if (index % 2 == 0) {
                        vehicle = new Car("CONCURRENT-CAR-" + index, "COLOR-" + index);
                    } else {
                        vehicle = new Bike("CONCURRENT-BIKE-" + index, "COLOR-" + index);
                    }
                    
                    Ticket ticket = manager.parkVehicle(vehicle);
                    if (ticket != null) {
                        synchronized (tickets) {
                            tickets.add(ticket);
                        }
                    }
                } catch (Exception e) {
                    System.out.println("  ✗ Error in thread " + index + ": " + e.getMessage());
                }
            });
        }
        
        executor.shutdown();
        boolean completed = executor.awaitTermination(10, TimeUnit.SECONDS);
        
        System.out.printf("\n✓ Concurrent operation completed: %b\n", completed);
        System.out.printf("✓ Successfully parked: %d vehicles\n", tickets.size());
        
        manager.displayAvailability();
        
        // Cleanup
        System.out.println("\n→ Unparking all concurrent vehicles...");
        for (Ticket t : tickets) {
            try {
                manager.unparkVehicle(t);
            } catch (Exception e) {
                // Ignore errors during cleanup
            }
        }
    }

    /**
     * Demo 5: Real-time availability tracking
     */
    private static void demo5_Availability(ParkingManager manager) {
        printSection("DEMO 5: Real-Time Availability Tracking");
        
        System.out.println("\n→ Current parking lot status:");
        manager.displayAvailability();
        
        // Park some vehicles
        System.out.println("→ Parking multiple vehicles...");
        Vehicle car = new Car("DEMO-AVL-1", "RED");
        Ticket t1 = manager.parkVehicle(car);
        
        Vehicle bike = new Bike("DEMO-AVL-2", "BLUE");
        Ticket t2 = manager.parkVehicle(bike);
        
        System.out.println("\n→ Status after parking 2 vehicles:");
        manager.displayAvailability();
        
        // Cleanup
        if (t1 != null) manager.unparkVehicle(t1);
        if (t2 != null) manager.unparkVehicle(t2);
    }

    /**
     * Demo 6: Error handling and edge cases
     */
    private static void demo6_EdgeCases(ParkingManager manager) {
        printSection("DEMO 6: Error Handling & Edge Cases");
        
        System.out.println("\n→ Test 1: Attempt to park null vehicle");
        try {
            manager.parkVehicle(null);
            System.out.println("  ✗ Should have thrown exception");
        } catch (IllegalArgumentException e) {
            System.out.println("  ✓ Correctly caught: " + e.getMessage());
        }
        
        System.out.println("\n→ Test 2: Attempt to unpark null ticket");
        try {
            manager.unparkVehicle(null);
            System.out.println("  ✗ Should have thrown exception");
        } catch (IllegalArgumentException e) {
            System.out.println("  ✓ Correctly caught: " + e.getMessage());
        }
        
        System.out.println("\n→ Test 3: Invalid vehicle data");
        try {
            new Car(null, "RED");
            System.out.println("  ✗ Should have thrown exception");
        } catch (IllegalArgumentException e) {
            System.out.println("  ✓ Correctly caught: " + e.getMessage());
        }
        
        System.out.println("\n→ Test 4: Double exit (exit same ticket twice)");
        Vehicle car = new Car("EDGE-1", "RED");
        Ticket ticket = manager.parkVehicle(car);
        if (ticket != null) {
            manager.unparkVehicle(ticket);
            System.out.println("  ✓ First exit successful");
            
            try {
                manager.unparkVehicle(ticket);
                System.out.println("  ✗ Should have thrown exception");
            } catch (IllegalStateException e) {
                System.out.println("  ✓ Correctly prevented double exit: " + e.getMessage());
            }
        }
    }

    /**
     * Helper method to print section headers
     */
    private static void printSection(String title) {
        System.out.println("\n" + "=".repeat(70));
        System.out.println(title);
        System.out.println("=".repeat(70));
    }

    /**
     * Helper method to print main header
     */
    private static void printHeader(String title) {
        System.out.println("\n╔" + "═".repeat(68) + "╗");
        System.out.println("║  " + String.format("%-64s", title) + "  ║");
        System.out.println("╚" + "═".repeat(68) + "╝");
    }
}
