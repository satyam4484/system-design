#include <iostream>
#include <vector>

// Interface for restaurant employees
class RestaurantEmployee {
public:
    virtual void performDuties() = 0;
};

// Interface for waiters
class WaiterInterface {
public:
    virtual void serveCustomers() = 0;
    virtual void takeOrders() = 0;
};

// Interface for chefs
class ChefInterface {
public:
    virtual void cookFood() = 0;
    virtual void decideMenu() = 0;
};

// Waiter class implementing WaiterInterface
class Waiter : public RestaurantEmployee, public WaiterInterface {
public:
    void performDuties() override {
        serveCustomers();
        takeOrders();
    }

    void serveCustomers() override {
        std::cout << "Serving the customers" << std::endl;
    }

    void takeOrders() override {
        std::cout << "Taking orders from customers" << std::endl;
    }
};

// Chef class implementing ChefInterface
class Chef : public RestaurantEmployee, public ChefInterface {
public:
    void performDuties() override {
        decideMenu();
        cookFood();
    }

    void cookFood() override {
        std::cout << "Cooking delicious food" << std::endl;
    }

    void decideMenu() override {
        std::cout << "Deciding the menu for today" << std::endl;
    }
};

int main() {
    // Create instances of waiter and chef
    Waiter waiter;
    Chef chef;

    // Perform duties
    std::cout << "Waiter's duties:" << std::endl;
    waiter.performDuties();
    std::cout << std::endl;

    std::cout << "Chef's duties:" << std::endl;
    chef.performDuties();

    return 0;
}
