# Interface Segregation Principle Problem Statement

## Problem Description

You have been assigned to design a system for managing employees at a restaurant. The system should handle different roles such as waiters and chefs efficiently.

## Design Considerations

When designing the system, adhere to the Interface Segregation Principle (ISP), which states that clients should not be forced to depend on interfaces they do not use. In other words, keep interfaces segregated so that users only need to know about the methods that are relevant to them.

Consider the following scenario:

1. Define an interface `RestaurantEmployee` with methods such as `washDishes()`, `serveCustomers()`, and `cookFood()`.
2. Implement classes such as `Waiter` and `Chef` that inherit from the `RestaurantEmployee` interface.
3. Ensure that each class implements only the methods relevant to its role. For example, the `Waiter` class should implement `serveCustomers()` and `takeOrders()`, while the `Chef` class should implement `cookFood()` and `decideMenu()`.
4. Avoid implementing unnecessary methods in classes where they are not relevant, adhering to the ISP.

## Solution Approach

Follow these guidelines to adhere to the Interface Segregation Principle:

1. **Interface Definition:** Define an interface (`RestaurantEmployee`) with methods relevant to various roles in the restaurant.
2. **Class Implementation:** Implement classes (`Waiter`, `Chef`) that inherit from the interface and implement only the methods relevant to their role.
3. **Avoid Unnecessary Methods:** Ensure that each class implements only the methods necessary for its functionality. Avoid implementing unnecessary methods that do not belong to a particular role.
4. **Interface Segregation:** Verify that each class interface is segregated, ensuring that clients only depend on methods relevant to their needs.

## Conclusion

By adhering to the Interface Segregation Principle, you ensure that classes have lean and focused interfaces, reducing coupling and making the system easier to maintain and extend. This approach leads to more cohesive and flexible designs, where each class is responsible for a specific set of functionalities without unnecessary dependencies.