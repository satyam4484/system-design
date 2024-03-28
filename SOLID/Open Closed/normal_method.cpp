#include <iostream>
#include <string>

// Payment processing function without adherence to OCP
void processPayment(std::string paymentMethod, double amount) {
    if (paymentMethod == "CreditCard") {
        std::cout << "Processing credit/debit card payment of $" << amount << std::endl;
        // Logic to process credit/debit card payment
    } else if (paymentMethod == "PayPal") {
        std::cout << "Processing PayPal payment of $" << amount << std::endl;
        // Logic to process PayPal payment
    } else if (paymentMethod == "DigitalWallet") {
        std::cout << "Processing digital wallet payment of $" << amount << std::endl;
        // Logic to process digital wallet payment
    } else {
        std::cout << "Invalid payment method!" << std::endl;
    }
}

int main() {
    // Process payments using normal method
    processPayment("CreditCard", 100.0);
    processPayment("PayPal", 50.0);
    processPayment("DigitalWallet", 30.0);
    processPayment("Bitcoin", 200.0); // Invalid payment method

    return 0;
}
