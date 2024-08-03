#include "NormalAccount.h"

// NormalAccount::NormalAccount(const string& accNum, const string& nm, int bal)
//     : Account(accNum, nm, bal) {}

void NormalAccount::showAccInfo() const {
    cout << "[보통예금계좌]";
    Account::showAccInfo();
}

void NormalAccount::save(ofstream& outFile) const {
    outFile << "N ";
    Account::save(outFile);
}