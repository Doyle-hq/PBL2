#ifndef EMPLOYEE_REPOSITORY_H
#define EMPLOYEE_REPOSITORY_H

#include "../Models/Employee.h"
#include <vector>
#include <string>
using namespace std;

class EmployeeRepository {
private:
    string fileName;

public:
    EmployeeRepository(string fileName = "Data/Employee.txt");

    vector<Employee> getAll();
    bool saveAll(const vector<Employee>& employees);

    bool add(const Employee& employee);
    bool update(const Employee& employee);
    bool remove(string NV_ID);

    bool findByID(string NV_ID, Employee& employee);
};

#endif