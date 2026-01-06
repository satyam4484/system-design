package Parking_Lot_system.strategy.payment;


public class CashPaymentStrategy implements PaymentStrategy {

    @Override
    public boolean pay(double amount) {
        // assume cash payment always succeeds
        return true;
    }
}
