
#include<bits/stdc++.h>
#include<iostream>
#include"ShapeManager.cpp"
#include "Shape.cpp"

using namespace std;


int main() {
    // Create instances of different shapes dynamically
    Shape* rectangle = new Rectangle(5, 3);
    Shape* square = new Square(4);
    Shape* circle = new Circle(2);

    // Add shapes to a vector
    std::vector<Shape*> shapes;
    shapes.push_back(rectangle);
    shapes.push_back(square);
    shapes.push_back(circle);

    // Calculate total area of all shapes
    ShapeManager shapeManager;
    double totalArea = shapeManager.calculateTotalArea(shapes);
    std::cout << "Total area of all shapes: " << totalArea << std::endl;

    // Free memory allocated to shapes
    for (Shape* shape : shapes) {
        delete shape;
    }
    return 0;
}
