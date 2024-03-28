#include <bits/stdc++.h>

#include "PaymentMethod.cpp"

using namespace std;

void processPayment(PaymentMethod *method, double amount){
    method->processPayment(amount);
}

int main() {
    // Process payments using OCP-compliant method
    PaymentMethod *creditCard = new CreditCardPayment();
    PaymentMethod *payPal = new PayPalPayment();
    PaymentMethod *digitalWallet = new DigitalWalletPayment();

    processPayment(creditCard, 100.0);
    processPayment(payPal, 50.0);
    processPayment(digitalWallet, 30.0);

    delete creditCard;
    delete payPal;
    delete digitalWallet;

    return 0;
}