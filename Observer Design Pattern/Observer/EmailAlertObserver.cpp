#pragma once

#include<bits/stdc++.h>
#include "NotificationAlertObserver.cpp"
#include "../Observable/StocksObservable.cpp"

using namespace std;


// observer concrete class with method to notify via email
class EmailAlertObserver:public NotificationAlertObserver {
    string emailId;
    stocksObservable *observable;
public:

    EmailAlertObserver(string emailId,stocksObservable *observable) {
        this->emailId = emailId;
        this->observable = observable;
    }

    void update(){
        cout<<"Sending mail to "<<emailId<<" \n With Message Hurry up the product is in stock now"<<endl;
    }
};