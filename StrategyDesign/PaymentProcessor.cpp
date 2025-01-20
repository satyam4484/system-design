#include<bits/stdc++.h>

#include "./PaymentStrategy.cpp"

class PaymentProcessor {
    private:
        PaymentStrategy* paymentStrategy;

    public:
        PaymentProcessor(PaymentStrategy* paymentStrategy) {
            this->paymentStrategy = paymentStrategy;
        }

        void processPayment(double amount) {
            paymentStrategy->pay(amount);
        }
};