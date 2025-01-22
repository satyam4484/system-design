#include<iostream>
#include<bits/stdc++.h>
#include "Observer.cpp"
#include "Observable.cpp"
using namespace std;


int main() {

    // Create an observable object
    Iphone iphone("Iphone 12", 10);
    
    User user("John", "john@gmail.com");

    // Attach the observer to the observable object
    iphone.attach(&user);

    iphone.setStockCount(5);

    return 0;
}