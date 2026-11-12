#include "Account.h"

Account::Account() {
    pass = "";
    role = "";
    NV_ID = "";
    isLocked = false;
}

Account::Account(string pass, string role, string NV_ID, bool isLocked) {
    this->pass = pass;
    this->role = role;
    this->NV_ID = NV_ID;
    this->isLocked = isLocked;
}

string Account::getPass() const {
    return pass;
}

string Account::getRole() const {
    return role;
}

string Account::getNV_ID() const {
    return NV_ID;
}

bool Account::getIsLocked() const {
    return isLocked;
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

void Account::setIsLocked(bool isLocked) {
    this->isLocked = isLocked;
}