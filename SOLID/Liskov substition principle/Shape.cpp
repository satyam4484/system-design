#pragma once
#include<bits/stdc++.h>
using namespace std;

class Shape{
public:
    virtual double calculateArea() =0;
};

class Rectangle:public Shape{
private:
    double length,width;
public:
    Rectangle(double l,double w):length(l),width(w) {}

    double calculateArea() {
        return length*width;
    }
};

class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}

    double calculateArea() override {
        return side * side;
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double calculateArea() override {
        return M_PI * radius * radius;
    }
};