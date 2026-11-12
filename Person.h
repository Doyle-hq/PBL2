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

    string getFullName() const;
    string getDateOfBirth() const;
    string getGender() const;
    string getPhone() const;
    string getAddress() const;

    void setFullName(string fullName);
    void setDateOfBirth(string dateOfBirth);
    void setGender(string gender);
    void setPhone(string phone);
    void setAddress(string address);
};

#endif