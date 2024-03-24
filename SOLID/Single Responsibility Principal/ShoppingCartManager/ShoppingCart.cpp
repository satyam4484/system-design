#include <bits/stdc++.h>
using namespace std;

class ShoppingCartItems {
public:
    string name;    // Name of the item.
    double price;   // Price of the item.
};

class ShoppingCartManager {
private:
    vector<ShoppingCartItems> cart; // Vector to store shopping cart items.
public:
    // Function to add an item to the shopping cart.
    void addItem(const string &name, const double &price) {}

    // Function to remove an item from the shopping cart.
    void removeItem(const string &name) {}

    // Function to calculate the total price of items in the shopping cart.
    double calculateTotal() {}

    // Function to display the items in the shopping cart.
    void displayCart() {}
};
