#include<iostream>
#include<bits/stdc++.h>
#include "PaymentProcessor.cpp"
#include "PaymentStrategy.cpp"
using namespace std;

int main() {

    cout << "Starting the process of Payment" << endl;

    // old method using delete

    // CreditCardPayment *creditCardPayment = new CreditCardPayment("123456678");

    // CashPayment *cashPayment = new CashPayment();

    // PaymentProcessor *paymentProcessor = new PaymentProcessor(&(*creditCardPayment));
    // paymentProcessor->processPayment(1000);
    // delete creditCardPayment;

    // paymentProcessor = new PaymentProcessor(&(*cashPayment));
    // paymentProcessor->processPayment(1000);
    // delete cashPayment;


    // new method using smart pointers
    unique_ptr<CreditCardPayment>creditCardPayment = make_unique<CreditCardPayment>("123");
    unique_ptr<CashPayment>cashPayment = make_unique<CashPayment>();

    PaymentProcessor paymentProcessor(&(*creditCardPayment));
    paymentProcessor.processPayment(1000);

    paymentProcessor = PaymentProcessor(&(*cashPayment));
    paymentProcessor.processPayment(1000);

    return 0;
}