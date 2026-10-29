#ifndef MANAGE_H
#define MANAGE_H

#include "Person.h"
#include "Employee.h"
#include <vector>
#include <string>

#include <vector>

class Manage : public Person{
private:
    vector<Employee> listEmployee;

public:
    Manage();
    Manage(string fullName, string dateOfBirth, string gender, string phone, string address);
    
    //quản lý
    void addEmployee();
    void removeEmployee();
    void updateEmployee();

    //tìm kiếm
    void seachID();
    void seachName();

    //sắp xếp
    void arrangeID();
    void arrangeName();
    void arrangePHG_ID();

    //lọc
    void filterPHG_ID();

    //lưu file
    void savefile();

    //đọc file
    void readfile();

    void displayList();
    bool displayEmployeeByID(string NV_ID);

    void menu();
};

#endif
