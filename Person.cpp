
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

string Person::getFullName() {
    return fullName;
}

string Person::getDateOfBirth() {
    return dateOfBirth;
}

string Person::getGender() {
    return gender;
}

string Person::getPhone() {
    return phone;
}

string Person::getAddress() {
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

void Person::displayInfo() {
    cout << "Ho ten: " << fullName << endl;
    cout << "Ngay sinh: " << dateOfBirth << endl;
    cout << "Gioi tinh: " << gender << endl;
    cout << "So dien thoai: " << phone << endl;
    cout << "Dia chi: " << address << endl;
}
