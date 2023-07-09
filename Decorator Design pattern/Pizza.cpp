
#pragma once   // this is written so the there should not be conflic between the files


// interface for the pizza base
class BasePizza{
    public:
    virtual int cost() = 0;
};

// types of base pizza
class FarmHouse:public BasePizza{
    public:
    int cost() {return 150;}
};

class VegDelight:public BasePizza {
    public:
    int cost() {return 160;}
};

class Margherita:public BasePizza{
public:
    int cost(){return 200;}    
};

