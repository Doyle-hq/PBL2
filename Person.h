#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

class Person{
protected:
    string fullName;
    string dateOfBirth;
    string gender;
    string phone;
    string address;

public:
    Person();
    Person(string fullName, string dateOfBirth, string gender, string phone, string address);

    string getFullName();
    string getDateOfBirth();
    string getGender();
    string getPhone();
    string getAddress();

    void setFullName(string fullName);
    void setDateOfBirth(string dateOfBirth);
    void setGender(string gender);
    void setPhone(string phone);
    void setAddress(string address);

    void displayInfo();
};

#endif
