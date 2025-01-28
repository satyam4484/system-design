#pragma once
#include<iostream>
#include "Pizza.cpp"
#include<bits/stdc++.h>
using namespace std;

class PizzaFactor{
    public:
    pizza *createPizza(string type){
        if(type == "Cheeze"){
            return new CheezePizza();
        }
        else if(type == "Chiken"){
            return new ChikenPizza();
        }
        return NULL;
    }
};


