#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "Account.h"

using namespace std;

class User {
    string name;
    // unordered_map<string, unique_ptr<Account>> accountMap;
    map<string, unique_ptr<Account>> accountMap;
public:
    User(const string& userName) : name(userName) {}

    string getName();
    void addAccount(const string& accountNumber, unique_ptr<Account> account);
    Account* getAccount(const string& accountNumber) const;
    void showAllAccounts() const;               // 유저 show
    void saveAccounts(ofstream& outFile) const; // 유저 저장
    void loadAccounts(ifstream& inFile);        // 불러오기
};

#endif // USER_H