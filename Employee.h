#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include <string>
using namespace std;

class Employee : public Person{
private:
    string NV_ID;
    string PHG_ID; //mã phòng ban
    string ngayVaoLam;
    string status; //trang thai
public:
    Employee();
    Employee(string NV_ID, string fullName, string dateOfBirth, string gender, string phone, string address, string PHG_ID, string ngayVaoLam, string status);

    string getNV_ID();
    string getPHG_ID();
    string getNgayVaoLam();
    string getStatus();

    void setNV_ID(string NV_ID);
    void setPHG_ID(string PHG_ID);
    void setNgayVaoLam(string ngayVaoLam);
    void setStatus(string status);

    void displayInfo();
};

#endif
