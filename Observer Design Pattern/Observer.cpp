#pragma once
#include<iostream>
using namespace std;

class Observer{
    public:
        virtual void update(string &product, int count) = 0;
        virtual ~Observer() = default;
};



class User:public Observer{
    string name;
    string email;
    public:
        User(string name, string email): name(name), email(email){};

        void update(string &product, int count){
            cout<<"hello "<<name<<", "<<product<<" is now available. There are "<<count<<" items in stock."<<endl;
        }
};

