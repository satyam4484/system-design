#pragma once
#include<iostream>
#include "Observer.cpp"
using namespace std;

class Subject{
    public:
        virtual void attach(Observer *observer) = 0;
        virtual void detach(Observer *observer) = 0;
        virtual void notify() = 0;
        virtual ~Subject() = default;
};


class Iphone: public Subject {
    string name;
    int stockCount;
    vector<Observer*>observers;

    public:
        Iphone(string name, int stockCount): name(name), stockCount(stockCount){};

        void setStockCount(int stockCount){
            this->stockCount = stockCount;
            this->notify();
        }

        void attach(Observer *observer) {
            this->observers.push_back(observer);
        }

        void detach(Observer *observer) {
            this->observers.erase(remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());
        }

        void notify() {
            for(auto observer: this->observers){
                observer->update(this->name, this->stockCount);
            }
        }
};
