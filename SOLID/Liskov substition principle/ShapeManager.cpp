#pragma once
#include<bits/stdc++.h>
using namespace std;
#include "Shape.cpp"

class ShapeManager {
public:
    double calculateTotalArea(std::vector<Shape*>& shapes) {
        double totalArea = 0;
        for (Shape* shape : shapes) {
            totalArea += shape->calculateArea();
        }
        return totalArea;
    }
};

