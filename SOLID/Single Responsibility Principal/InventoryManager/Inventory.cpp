#include<bits/stdc++.h>
using namespace std;

class Book {
public:
    string title, author;  // Title and author of the book.
    int quantity;          // Quantity of the book in the inventory.
    double price;          // Price of the book.
};

class InventoryManager {
private:
    vector<Book> inventory;  // Vector to store books in the inventory.
public:
    // Function to add a book to the inventory.
    void addBook(const string &title, const string &author, const int &quantity, const double &price) {}

    // Function to remove a book from the inventory.
    void removeBook(const string &title) {}

    // Function to display the inventory.
    void displayInventory() {}
};