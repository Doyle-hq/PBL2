#include "Account.h"

Account::Account() {
    pass = "";
    role = "";
    NV_ID = "";
}

Account::Account(string pass, string role, string NV_ID) {
    this->pass = pass;
    this->role = role;
    this->NV_ID = NV_ID;
}

string Account::getPass() {
    return pass;
}

string Account::getRole() {
    return role;
}

string Account::getNV_ID() {
    return NV_ID;
}

void Account::setPass(string pass) {
    this->pass = pass;
}

void Account::setRole(string role) {
    this->role = role;
}

void Account::setNV_ID(string NV_ID) {
    this->NV_ID = NV_ID;
}
