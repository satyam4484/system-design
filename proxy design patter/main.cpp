#include<iostream>
#include "interface.cpp"

#include<bits/stdc++.h>
using namespace std;
int main() {
    Employee *employee = new EmployeeProxy();
    employee->create("ADMIN",new EmployeeImpl());

    return 0;
}