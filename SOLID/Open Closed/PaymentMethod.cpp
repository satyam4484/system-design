#include<bits/stdc++.h>
using namespace std;

class PaymentMethod {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentMethod() {}
};


class CreditCardPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing credit/debit card payment of $" << amount << endl;
        // Logic to process credit/debit card payment
    }
};

class PayPalPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
        // Logic to process PayPal payment
    }
};

class DigitalWalletPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing digital wallet payment of $" << amount << endl;
        // Logic to process digital wallet payment
    }
};