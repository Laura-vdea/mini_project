#include "NormalAccount.h"
#include "User.h"

string User::getName()  {
    return name;
}

void User::addAccount(const string& accountNumber, unique_ptr<Account> account) {
    accountMap[accountNumber] = move(account);
}

Account* User::getAccount(const string& accountNumber) const {
    auto it = accountMap.find(accountNumber);
    return (it != accountMap.end()) ? it->second.get() : nullptr;
}

void User::showAllAccounts() const {
    for (const auto& pair : accountMap) {
        pair.second->showAccInfo();
    }
}

void User::saveAccounts(ofstream& outFile) const {
    for (const auto& pair : accountMap) {
        pair.second->save(outFile);
    }
}

void User::loadAccounts(ifstream& inFile) {
    accountMap.clear();
    char accountType;
    while (inFile >> accountType) {
        string accountNumber, name;
        int balance;
        if (accountType == 'N') {
            inFile >> accountNumber >> name >> balance;
            accountMap[accountNumber] = make_unique<NormalAccount>(accountNumber, name, balance);
        }
    }
}