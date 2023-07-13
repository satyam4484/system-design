#pragma once
#include <bits/stdc++.h>
using namespace std;


class Employee{
    public:
    virtual void create(string client,Employee*obj) = 0;
    virtual void Delete(string client,Employee *obj) = 0;

};


class EmployeeImpl:public Employee{
public:
    void create(string client,Employee *obj) {
        cout<<"created a new employee"<<endl;
    }

    void Delete(string client,Employee*obj) {
        cout<<"Deleted the Employee"<<endl;
    } 
};

class EmployeeProxy:public Employee{
    public:
    Employee *employee;
    EmployeeProxy() {
        this->employee = new EmployeeImpl();
    }

    void create(string client,Employee *obj) {
        if(client == "ADMIN") {
            employee->create(client,obj);
            return;
        }else{
            cout<<"Invalid User"<<endl;
        }
    }

    void Delete(string client,Employee*obj) {
        if(client =="ADMIN") {
            employee->Delete(client,obj);
            return;
        }else{
            cout<<"Invalid User"<<endl;
        }
    }
};