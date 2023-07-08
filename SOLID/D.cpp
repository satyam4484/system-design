#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// class should depend on interfaces rather than concrete classes
//**************************************************************
// Interfaces
class Keyboard{};
class Mouse{};

class wiredKeyboard:public Keyboard{};
class wireLessKeyboard:public Keyboard{};

class wiredMouse:public Mouse{};
class wireLessMouse:public Mouse{};

// conside the below class it points out to conrete class not the interface
class Mackbook{
    wiredKeyboard keyboard;
    wiredMouse mouse;
};

// *******************************************************************
// so the macbook class can be replace with 
class MACKBOOK{
    Keyboard keyboard;
    Mouse mouse;
};


int main() {
    
    return 0;
}