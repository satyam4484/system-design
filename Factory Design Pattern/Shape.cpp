#pragma once
#include<bits/stdc++.h>
using namespace std;

// <<Interface>>
class Shape{
    public:
    virtual void draw () = 0;
};


// concrete classes having is a relationship with the Shape class
class Circle:public Shape{
public:
    void draw() {
        cout<<"Draw a circle"<<endl;
    }
};

class Rectangle:public Shape{
public:
    void draw() {
        cout<<"Draw a rectangle"<<endl;
    }
};

class Square:public Shape{
public:
    void draw() {
        cout<<"Draw a square"<<endl;
    }
};



