#pragma once
#include<iostream>

using namespace std;


class PaymentStrategy {
    public:
        virtual void pay(double amount) = 0;
        virtual ~PaymentStrategy() = default; 
};


class CreditCardPayment: public PaymentStrategy{
    private:
        string cardNumber;
    public:
        CreditCardPayment(string cardNumber) {
            this->cardNumber = cardNumber;
        }

        void pay(double amount) override {
            cout << "Paying " << amount << " using credit card " << cardNumber << endl;
        }

        ~CreditCardPayment() {
            cout << "Credit card payment object destroyed" << endl;
        }
};

class CashPayment: public PaymentStrategy{
    public:
        void pay(double amount) override {
            cout << "Paying " << amount << " using cash" << endl;
        }

        ~CashPayment() {
            cout << "Cash payment object destroyed" << endl;
        }
};



