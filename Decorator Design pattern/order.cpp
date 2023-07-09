#include<iostream>
#include<bits/stdc++.h>
#include "Pizza.cpp"
#include "Toppings.cpp"


using namespace std;
int main() {

    // we are ordering the pizza with mushroom and exta cheese
    BasePizza *pizza= new Mushroom(new ExtraCheese(new VegDelight())); 

    cout<<pizza->cost()<<endl; // getting the final cost of the pizza
    
    return 0;
}