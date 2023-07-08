#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Marker{
    // take the datamembers and methods from S.cpp
    public:
    string name,color;
    int year,price;
};

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

class InvoiceDb:public Invoice{
    Invoice invoice;
public:
    InvoiceDb(Invoice invoice){
        invoice = invoice;
    }

    void saveToDb() {
        // save to database
    }

    void saveToFile() {
        // further requirements comes to save to file 
    }
};

// as you can see we have modified the existing InvoiceDb which should not be happen
// *********************************************************************************

// interface in c++ is implemented using abstract class in c++
class SaveInvoice{
    virtual void save(Invoice invoice) =0;
};  



class saveToDatabase:public SaveInvoice{
public:
    void save(Invoice invoice) {
        // save to database
    }
};

class saveToFile:public SaveInvoice{
public:
    void save(Invoice invoice) {
        // save data to file
    }
};

// in this way we  implemented the open closed principal using abstract classes in c++
// *********************************************************************************

int main() {
    
    return 0;
}