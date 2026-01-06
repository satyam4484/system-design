package Parking_Lot_system.strategy.pricing;

import Parking_Lot_system.model.Ticket;

public interface PricingStrategy {
    double calculateFee(Ticket ticket);
}
