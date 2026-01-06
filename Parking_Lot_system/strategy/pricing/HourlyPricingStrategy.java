package Parking_Lot_system.strategy.pricing;

import java.time.Duration;
import java.time.LocalDateTime;

import Parking_Lot_system.model.Ticket;

public class HourlyPricingStrategy implements PricingStrategy {

    private static final double HOURLY_RATE = 50.0;

    @Override
    public double calculateFee(Ticket ticket) {
        LocalDateTime entry = ticket.getEntryTime();
        LocalDateTime exit = ticket.getExitTime();

        long hours = Math.max(
                5,
                Duration.between(entry, exit).toHours()
        );

        return hours * HOURLY_RATE;
    }
}
