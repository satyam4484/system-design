#include<bits/stdc++.h>
#include "BookManager.cpp"
#include "../InventoryManager/Inventory.cpp"
#include "../OrderManager/OrderManager.cpp"
#include "../Reports/ReportsGenerator.cpp"
#include "../ShoppingCartManager/ShoppingCart.cpp"
#include "../UserManager/User.cpp"

using namespace std;

class BookStore{
private:
    User usermanager;
    BookManager bookManager;
    ShoppingCartManager shoppingCartManager;
    OrderManager orderManager;
    InventoryManager inventoryManager;
    ReportsGenerator reportGenerator;
public:
    void run(){
        cout<<"Welcome to online Book management"<<endl;

        usermanager.addUser("Satyam","password123");
        bookManager.addBook("The Great Gatsby", "F. Scott Fitzgerald", 15.99);
        bookManager.addBook("To Kill a Mockingbird", "Harper Lee", 12.50);

        inventoryManager.addBook("The Great Gatsby", "F. Scott Fitzgerald", 10, 15.99);
        inventoryManager.addBook("To Kill a Mockingbird", "Harper Lee", 20, 12.50);

        inventoryManager.displayInventory();

        shoppingCartManager.addItem("The Great Gatsby", 15.99);
        shoppingCartManager.addItem("To Kill a Mockingbird", 12.50);
        double total = shoppingCartManager.calculateTotal();
        orderManager.placeOrder("Satyam", {"The Great Gatsby", "To Kill a Mockingbird"}, total);
        reportGenerator.generateSalesReport({15.99, 12.50});
    }
};