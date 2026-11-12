#include "Employee.h"

Employee::Employee() : Person(){
    NV_ID = "";
    PHG_ID = "";
    ngayVaoLam = "";
    status = "Dang lam";
}

Employee::Employee(string NV_ID, string fullName, string dateOfBirth, string gender, string phone, string address, string PHG_ID, string ngayVaoLam, string status) : Person(fullName, dateOfBirth, gender, phone, address){
    this->NV_ID = NV_ID;
    this->PHG_ID = PHG_ID;
    this->ngayVaoLam = ngayVaoLam;
    this->status = status;
}

string Employee::getNV_ID() const {
    return NV_ID;
}

string Employee::getPHG_ID() const {
    return PHG_ID;
}

string Employee::getNgayVaoLam() const {
    return ngayVaoLam;
}

string Employee::getStatus() const {
    return status;
}
    
void Employee::setNV_ID(string NV_ID){
    this->NV_ID = NV_ID;
}

void Employee::setPHG_ID(string PHG_ID){
    this->PHG_ID = PHG_ID;
}

void Employee::setNgayVaoLam(string ngayVaoLam){
    this->ngayVaoLam = ngayVaoLam;
}

void Employee::setStatus(string status){
    this->status = status;
}