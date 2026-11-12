#include "Person.h"

Person::Person() {
    fullName = "";
    dateOfBirth = "";
    gender = "";
    phone = "";
    address = "";
}

Person::Person(string fullName, string dateOfBirth, string gender, string phone, string address) {
    this->fullName = fullName;
    this->dateOfBirth = dateOfBirth;
    this->gender = gender;
    this->phone = phone;
    this->address = address;
}

string Person::getFullName() const {
    return fullName;
}

string Person::getDateOfBirth() const {
    return dateOfBirth;
}

string Person::getGender() const {
    return gender;
}

string Person::getPhone() const {
    return phone;
}

string Person::getAddress() const {
    return address;
}

void Person::setFullName(string fullName) {
    this->fullName = fullName;
}

void Person::setDateOfBirth(string dateOfBirth) {
    this->dateOfBirth = dateOfBirth;
}

void Person::setGender(string gender) {
    this->gender = gender;
}

void Person::setPhone(string phone) {
    this->phone = phone;
}

void Person::setAddress(string address) {
    this->address = address;
}