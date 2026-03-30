/**
 * Defines the standard interface for payment processing across different providers.
 */
interface Payment {
    /**
     * Processes a payment for a specified amount.
     * 
     * @param amount The numerical value of the transaction to be processed.
     * 
     * Example:
     * payment.pay(250.00);
     */
    void pay(double amount);
}

/**
 * A third-party service provider for handling payments specifically in USD.
 */
class StripeService {
    /**
     * Executes a transaction using the Stripe API in US Dollars.
     * 
     * @param amount The amount in USD to be charged.
     * 
     * Example:
     * stripeService.payInDollars(50.0);
     */
    void payInDollars(double amount) {
        System.out.println("Stripe paid: $" + amount);
    }
}

/**
 * A third-party service provider for handling payments specifically in INR.
 */
class RazorpayService {
    /**
     * Executes a transaction using the Razorpay API in Indian Rupees.
     * 
     * @param amount The amount in INR to be charged.
     * 
     * Example:
     * razorpayService.processPaymentINR(1000.0);
     */
    void processPaymentINR(double amount) {
        System.out.println("Razorpay paid: ₹" + amount);
    }
}

/**
 * Adapter class that wraps StripeService to make it compatible with the Payment interface.
 * This allows the system to use Stripe without changing the client-side code.
 */
class StripeAdapter implements Payment {
    /** The underlying Stripe service instance used for execution. */
    private StripeService stripe = new StripeService();

    /**
     * Maps the standard pay call to Stripe's specific dollar payment method.
     * 
     * @param amount The amount to be processed via Stripe.
     * 
     * Example:
     * Payment p = new StripeAdapter();
     * p.pay(100.0);
     */
    @Override
    public void pay(double amount) {
        stripe.payInDollars(amount);
    }
}

/**
 * Adapter class that wraps RazorpayService to make it compatible with the Payment interface.
 * This enables seamless integration of Razorpay into the existing payment workflow.
 */
class RazorpayAdapter implements Payment {
    /** The underlying Razorpay service instance used for execution. */
    private RazorpayService razorpay = new RazorpayService();

    /**
     * Maps the standard pay call to Razorpay's specific INR payment method.
     * 
     * @param amount The amount to be processed via Razorpay.
     * 
     * Example:
     * Payment p = new RazorpayAdapter();
     * p.pay(5000.0);
     */
    @Override
    public void pay(double amount) {
        razorpay.processPaymentINR(amount);
    }
}

/**
 * Entry point for the application demonstrating the Adapter Design Pattern.
 * This class showcases how different payment gateways can be used interchangeably via a common interface.
 */
public class Main {
    /**
     * Main execution method to demonstrate polymorphic payment processing.
     * 
     * @param args Command line arguments (not used).
     */
    public static void main(String[] args) {
        // Using Stripe through the Adapter
        Payment stripePayment = new StripeAdapter();
        stripePayment.pay(100.0);

        // Using Razorpay through the Adapter
        Payment razorpayPayment = new RazorpayAdapter();
        razorpayPayment.pay(7500.0);
    }
}
