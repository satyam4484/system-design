#include<iostream>
#include<bits/stdc++.h>
#include "Shape.cpp"

using namespace std;

// It will the type of shape object based on the condition
class ShapeFactory{
public:
    Shape *getShape(string s) {

       if(s=="Circle") return new Circle();
       else if(s=="Rectangle") return new Rectangle();
       else if(s=="Square") return new Square();
       return nullptr;
    }

};


int main() {
    ShapeFactory *sp=new ShapeFactory();
    Shape *obj = sp->getShape("Circle");
    obj->draw();   
    return 0;
}