#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class DriveInterface{
    public:
    virtual void drive() = 0;
};


class NormalDrive:public DriveInterface{
    public:

    void drive() {
        cout<<"Normal drive method"<<endl;
    }
};


class SpecialDrive:public DriveInterface{
    public:
    void drive(){
        cout<<"Special Drive method"<<endl;
    }
};


