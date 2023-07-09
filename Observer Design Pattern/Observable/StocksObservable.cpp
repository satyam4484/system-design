#pragma once
#include "../Observer/NotificationAlertObserver.cpp"

using namespace std;

// This is the observable interface 
class stocksObservable{
public:
    virtual void add(NotificationAlertObserver *observer) = 0;
    virtual void remove(NotificationAlertObserver *observer) = 0;
    virtual void notify() = 0;
    virtual void setCount(int newCount) = 0;
    virtual int getStockCount () = 0;
};


