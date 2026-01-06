package Parking_Lot_system.strategy.payment;

public class CardPaymentStrategy implements PaymentStrategy {

    @Override
    public boolean pay(double amount) {
        // simulate payment gateway
        return Math.random() > 0.1; // 90% success
    }
}