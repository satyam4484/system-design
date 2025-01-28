#include<iostream>
#include "PizzaFactory.cpp"
using namespace std;

int main(){
    PizzaFactor *pf = new PizzaFactor();
    pizza *p = pf->createPizza("Chiken");
    p->prepare();
    p->bake();
    p->cut();
    return 0;
}