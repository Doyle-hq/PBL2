
#include "Account.h"


Account::Account() {
    pass = "";
    vale = "";
    NV_ID = "";
}

Account::Account(string pass, string vale, string NV_ID) {
    this->pass = pass;
    this->vale = vale;
    this->NV_ID = NV_ID;
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

void Account::setPass(string pass) {
    this->pass = pass;
}

void Account::setVale(string vale) {
    this->vale = vale;
}

void Account::setNV_ID(string NV_ID) {
    this->NV_ID = NV_ID;
}
