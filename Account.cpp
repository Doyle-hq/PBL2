
#include "Account.h"


Account::Account() {
    username = "";
    pass = "";
    vale = "";
    NV_ID = "";
}

Account::Account(string username, string pass, string vale, string NV_ID) {
    this->username = username;
    this->pass = pass;
    this->vale = vale;
    this->NV_ID = NV_ID;
}


string Account::getUserName() {
    return username;
}

string Account::getPass() {
    return pass;
}

string Account::getVale() {
    return vale;
}

string Account::getNV_ID() {
    return NV_ID;
}

void Account::setUserName(string username) {
    this->username = username;
}

void Account::setPass(string pass) {
    this->pass = pass;
}

void Account::setVale(string vale) {
    this->vale = vale;
}

void Account::setNV_ID(string NV_ID) {
    this->NV_ID = NV_ID;
}
