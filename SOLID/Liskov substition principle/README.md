# Liskov Substitution Principle Problem Statement

## Problem Description

You are tasked with developing a system for managing geometric shapes. The system should allow users to calculate the area of various shapes and perform other geometric operations.

## Design Considerations

When designing the system, adhere to the Liskov Substitution Principle (LSP), which states that objects of a superclass should be replaceable with objects of its subclasses without affecting the correctness of the program. In other words, subclasses should be substitutable for their base class without altering the desirable properties of the program.

Consider the following scenario:

1. Define a base class `Shape` with common properties and methods for geometric shapes, such as `calculateArea()` and `draw()`.
2. Implement subclasses such as `Rectangle`, `Square`, and `Circle`, each representing specific geometric shapes.
3. Ensure that each subclass properly inherits from the `Shape` class and implements its methods according to the behavior expected for that shape.
4. Verify that substituting any subclass object for a `Shape` object does not break the functionality of the program.

## Solution Approach

Follow these guidelines to adhere to the Liskov Substitution Principle:

1. **Base Class Definition:** Define a base class (`Shape`) with common properties and methods for geometric shapes.
2. **Subclass Inheritance:** Implement subclasses (`Rectangle`, `Square`, `Circle`) that inherit from the base class and specialize in specific shapes.
3. **Method Implementation:** Ensure that each subclass implements the methods (`calculateArea()`, `draw()`) according to the behavior expected for that shape.
4. **Substitutability Test:** Verify that substituting any subclass object for a `Shape` object does not break the functionality of the program. Test various scenarios to ensure correctness.



Ensure that substituting any subclass object for a `Shape` object in the `calculateTotalArea()` method does not affect the correctness of the calculation.

## Conclusion

By adhering to the Liskov Substitution Principle, you ensure that subclasses can seamlessly replace their base class without introducing unexpected behavior or breaking the functionality of the program. This approach leads to more maintainable and extensible systems with clear and predictable behavior.