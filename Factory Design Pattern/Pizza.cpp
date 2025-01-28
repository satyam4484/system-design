
#pragma once
#include<iostream>
using namespace std;

class pizza{
    public:
    virtual void prepare() = 0;
    virtual void bake() = 0;
    virtual void cut() = 0;
};

class CheezePizza : public pizza{
    public:
    void prepare(){
        cout << "Preparing Cheeze Pizza" << endl;
    }
    void bake(){
        cout << "Baking Cheeze Pizza" << endl;
    }
    void cut(){
        cout << "Cutting Cheeze Pizza" << endl;
    }
};

class ChikenPizza : public pizza{
    public:
    void prepare(){
        cout << "Preparing Chiken Pizza" << endl;
    }
    void bake(){
        cout << "Baking Chiken Pizza" << endl;
    }
    void cut(){
        cout << "Cutting Chiken Pizza" << endl;
    }
};