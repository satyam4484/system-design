#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class ResturantEmployee{
public:
    virtual void washDishes() = 0;
    virtual void serveCustomers() = 0;
    virtual void cookFood() = 0;
};  

class Waiter:public ResturantEmployee{
public:
    void washDishes() {
        // not the job of the waiter
    }

    void serveCustomers(){
        cout<<"Serving the customers"<<endl;
    }

    void cookFood() {
        // not the job of waiter
    }
};

// as you can se wee have implement unnecessary function for the waiter so that should not be there
// ************************************************************************************************

// *************************************
// interfaces 
class waiterInterface{
public:
    virtual void serveCustomers() = 0;
    virtual void takeOrders() = 0;
};

class chefInterface {
public:
    virtual void cookFood() = 0;
    virtual void decideMenu() = 0;
};
// *************************************

class Waiter:public waiterInterface{

};

class chef:public chefInterface{

};

// now we have separated the functionality and hence there are no unnecessary functions
// ***********************************************************************************************


int main() {

    
    return 0;
}