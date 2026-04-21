package interview.expects;

import java.util.concurrent.atomic.AtomicLong;

/**
 * Manages ticket generation and fare calculation.
 * 
 * SOLID Principles:
 * - Single Responsibility: Only manages tickets
 * - Dependency Inversion: Depends on PricingStrategy interface, not concrete implementation
 * - Thread Safe: Uses AtomicLong for ticket ID generation
 */
public class TicketManager {
    private final AtomicLong ticketIdCounter = new AtomicLong(1000);
    private final PricingStrategy pricingStrategy;

    public TicketManager(PricingStrategy pricingStrategy) {
        if (pricingStrategy == null) {
            throw new IllegalArgumentException("Pricing strategy cannot be null");
        }
        this.pricingStrategy = pricingStrategy;
    }

    /**
     * Generate a new parking ticket
     * 
     * @param vehicle Vehicle being parked
     * @param spot Spot where vehicle is parked
     * @return New ticket
     */
    public Ticket generateTicket(Vehicle vehicle, Spot spot) {
        if (vehicle == null || spot == null) {
            throw new IllegalArgumentException("Vehicle and spot cannot be null");
        }
        
        long ticketId = ticketIdCounter.incrementAndGet();
        return new Ticket(ticketId, vehicle, spot);
    }

    /**
     * Calculate fare when vehicle exits
     * 
     * @param ticket The parking ticket
     * @return Fare amount
     */
    public double calculateFare(Ticket ticket) {
        if (ticket == null) {
            throw new IllegalArgumentException("Ticket cannot be null");
        }

        if (ticket.hasExited()) {
            return ticket.getFare();
        }

        long durationMinutes = ticket.getDurationMinutes();
        VehicleType vehicleType = ticket.getVehicle().getType();
        
        double fare = pricingStrategy.calculateFare(durationMinutes, vehicleType);
        ticket.exit(fare);
        
        return fare;
    }

    /**
     * Update pricing strategy (allows for dynamic pricing changes)
     */
    public void setPricingStrategy(PricingStrategy pricingStrategy) {
        if (pricingStrategy == null) {
            throw new IllegalArgumentException("Pricing strategy cannot be null");
        }
        // Note: In production, would need synchronization if actively used
        // For now, this is typically set during initialization
    }
}
