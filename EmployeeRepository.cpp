#include "EmployeeRepository.h"
#include <fstream>

EmployeeRepository::EmployeeRepository(string fileName) {
    this->fileName = fileName;
}

vector<Employee> EmployeeRepository::getAll() {
    vector<Employee> employees;
    ifstream file(fileName);

    if (!file.is_open()) {
        return employees;
    }

    string NV_ID, fullName, dateOfBirth, gender;
    string phone, address, PHG_ID, ngayVaoLam, status;

    while (getline(file, NV_ID)) {
        if (!getline(file, fullName) ||
            !getline(file, dateOfBirth) ||
            !getline(file, gender) ||
            !getline(file, phone) ||
            !getline(file, address) ||
            !getline(file, PHG_ID) ||
            !getline(file, ngayVaoLam) ||
            !getline(file, status)) {
            break;
        }

        employees.push_back(Employee(
            NV_ID, fullName, dateOfBirth, gender,
            phone, address, PHG_ID, ngayVaoLam, status
        ));
    }

    file.close();
    return employees;
}

bool EmployeeRepository::saveAll(const vector<Employee>& employees) {
    ofstream file(fileName);

    if (!file.is_open()) {
        return false;
    }

    for (const Employee& employee : employees) {
        file << employee.getNV_ID() << endl;
        file << employee.getFullName() << endl;
        file << employee.getDateOfBirth() << endl;
        file << employee.getGender() << endl;
        file << employee.getPhone() << endl;
        file << employee.getAddress() << endl;
        file << employee.getPHG_ID() << endl;
        file << employee.getNgayVaoLam() << endl;
        file << employee.getStatus() << endl;
    }

    file.close();
    return true;
}

bool EmployeeRepository::add(const Employee& employee) {
    vector<Employee> employees = getAll();

    for (const Employee& item : employees) {
        if (item.getNV_ID() == employee.getNV_ID()) {
            return false;
        }
    }

    employees.push_back(employee);
    return saveAll(employees);
}

bool EmployeeRepository::update(const Employee& employee) {
    vector<Employee> employees = getAll();
    bool found = false;

    for (Employee& item : employees) {
        if (item.getNV_ID() == employee.getNV_ID()) {
            item = employee;
            found = true;
            break;
        }
    }

    if (!found) {
        return false;
    }

    return saveAll(employees);
}

bool EmployeeRepository::remove(string NV_ID) {
    vector<Employee> employees = getAll();
    bool found = false;

    for (int i = 0; i < employees.size(); i++) {
        if (employees[i].getNV_ID() == NV_ID) {
            employees.erase(employees.begin() + i);
            found = true;
            break;
        }
    }

    if (!found) {
        return false;
    }

    return saveAll(employees);
}

bool EmployeeRepository::findByID(string NV_ID, Employee& employee) {
    vector<Employee> employees = getAll();

    for (const Employee& item : employees) {
        if (item.getNV_ID() == NV_ID) {
            employee = item;
            return true;
        }
    }

    return false;
}