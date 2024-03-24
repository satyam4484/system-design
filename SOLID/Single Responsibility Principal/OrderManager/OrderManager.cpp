#include<bits/stdc++.h>
using namespace std;

class Order {
public:
    string customerName;        // Name of the customer placing the order.
    vector<string> items;       // Items included in the order.
    double totalPrice;          // Total price of the order.
};

class OrderManager {
private:
    vector<Order> orders;      // Vector to store orders.
public:
    // Function to place an order.
    void placeOrder(const string &customerName, const vector<string> &items, const double &totalPrice) {}

    // Function to display all orders.
    void displayOrders() {}
};