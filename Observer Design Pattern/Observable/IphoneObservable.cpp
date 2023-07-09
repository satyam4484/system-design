#pragma once

#include<bits/stdc++.h>
#include "StocksObservable.cpp"
#include "../Observer/NotificationAlertObserver.cpp"
using namespace std;


// this is the observable concrete class of particular product
class IphoneObservable:public stocksObservable{
public:
    list<NotificationAlertObserver*>observers;  // we are storing the observers who have subsribed
    int stockCount = 0;
    
    // adding the observers to subscribe list
    void add(NotificationAlertObserver *observer) {
        observers.push_back(observer);
    }

    // removing the obserever from subsribed list
    void remove(NotificationAlertObserver *observer) {
        observers.remove(observer);
    }

    // notify method to update the subsribers about particular update
    void notify() {
        for(auto observer:observers) {
            observer->update();
        }
    }

    // set the new count of product 
    void setCount(int newCount) {
        stockCount = newCount;
        notify();
    }

    // get the current count of item 
    int getStockCount() {return stockCount;}
};