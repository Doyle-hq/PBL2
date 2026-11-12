#ifndef MENU_H
#define MENU_H

#include "../Services/EmployeeService.h"
#include "../Services/AccountService.h"

class Menu {
private:
    EmployeeService employeeService;
    AccountService accountService;

    void managerMenu();
    void employeeMenu(const Account& account);

    void addEmployee();
    void updateEmployee();
    void deleteEmployee();
    void displayEmployees();
    void searchEmployee();
    void sortEmployees();
    void filterEmployees();

    void lockAccount();
    void unlockAccount();
    void resignEmployee();

    void displayEmployee(const Employee& employee);
    void displayEmployeeList(const vector<Employee>& employees);

public:
    Menu();

    void run();
};

#endif