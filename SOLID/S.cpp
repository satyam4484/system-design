#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Marker{

public:
    string name,color;
    int year,price;

    Marker(){}


    Marker(string name,string color,int year,int price) {
        name = name,color = color,year=year,price = price;
    }
};

// Invoice has a Marker 
class Invoice:public Invoice{
    Marker marker;
    int quantity;
public:
    Invoice(Marker marker,int quantity) {
        marker = marker;
        quantity = quantity;
    }
    // calculate the total cost of price
    int calculateTotal() {
        int price = marker.price * quantity;
        return price;
    }

    void printInvoice() {
        // print the invoice
    }

    void saveToDb() {
        //save the data to db
    }
};

// so we need to break the invoice class as it is violating the single responsibility principle
// *********************************************************************************************

// The above code violates the single responsibility principal so we need to break into classes

// this class will only calculate invoice and has only one reason to change
class Invoice:public Invoice{
    Marker marker;
    int quantity;
public:
    Invoice(){}

    Invoice(Marker marker,int quantity) {
        marker = marker;
        quantity = quantity;
    }
    // calculate the total cost of price
    int calculateTotal() {
        int price = marker.price * quantity;
        return price;
    }
};


// This class will save data to database and if furthur required 
// can be save to file as only one function need to be changed 
class InvoiceDb:public Invoice{
    Invoice invoice;
public:
    InvoiceDb(Invoice invoice) {
        invoice = invoice;
    }
    void saveToDb() {
        // save the invoice to database or file as per the requirements
    }
};

// This class will generate the invoice as per the required format 
// and can be changed as per the furthure requirements
class displayInvoice:public Invoice{
    Invoice invoice;
public:
    displayInvoice(Invoice invoice) {
        invoice= invoice;
    }
    void printInvoice() {
        // display the invoice
    }
};

// in this way we break the classes into single functionality classes that have only
// one reason to change
// ***********************************************************************************************

int main() {
    
    return 0;
}