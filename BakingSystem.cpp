#include "BankingSystem.h"
#include "NormalAccount.h"
bool BankingSystem::userLogin() {
    cout << "사용자 이름을 입력하세요: ";
    cin >> currentUser;
    // int n;
    if (userMap.find(currentUser) == userMap.end()) {
        userMap[currentUser] = make_unique<User>(currentUser);
    }
    cout << currentUser << "님 환영합니다!" << endl;
    return true;
}

void BankingSystem::makeAccount() {
    if (currentUser.empty()) {
        cout << "먼저 로그인하세요!" << endl;
        return;
    }
    int choice;
    cout << "1. 보통예금계좌" << endl;
    cout << "개설하실 계좌를 선택하세요 : ";
    cin >> choice;
    cout << endl;
    switch (choice) {
    case 1:
        makeNormalAccount();
        break;
    default:
        cout << "잘못된 선택입니다." << endl;
        break;
    }
}
void BankingSystem::makeNormalAccount() {
    string accountNumber, name;
    int money;
    cout << "[보통예금계좌]" << endl;
    cout << "계좌번호: "; cin >> accountNumber;
    cout << "고객명: "; cin >> name;
    cout << "입금하실 금액: "; cin >> money;
    userMap[currentUser]->addAccount(accountNumber, make_unique<NormalAccount>(accountNumber, name, money));
    cout << "계좌 개설을 성공했습니다." << endl;
}
void BankingSystem::deposit() {
    if (currentUser.empty()) {
        cout << "먼저 로그인하세요!" << endl;
        return;
    }
    string accountNumber;
    int money;
    cout << "입금하실 계좌번호를 입력하세요: "; cin >> accountNumber;
    cout << "금액: "; cin >> money;
    User* user = userMap[currentUser].get();
    Account* account = user->getAccount(accountNumber);
    if (account) {
        if (account->deposit(money)) {
            cout << money << "원 입금을 성공했습니다." << endl;
        }
        else {
            cout << "입금을 실패했습니다. 금액을 올바르게 입력해주세요." << endl;
        }
    }
    else {
        cout << "계좌번호를 올바르게 입력해주세요." << endl;
    }
}
void BankingSystem::withdraw() {
    if (currentUser.empty()) {
        cout << "먼저 로그인하세요!" << endl;
        return;
    }
    string accountNumber;
    int money;
    cout << "출금하실 계좌번호를 입력하세요: "; cin >> accountNumber;
    cout << "금액: "; cin >> money;
    User* user = userMap[currentUser].get();
    Account* account = user->getAccount(accountNumber);
    if (account) {
        if (account->withdraw(money)) {
            cout << money << "원 출금을 성공했습니다." << endl;
        }
        else {
            cout << "출금을 실패했습니다. 금액을 올바르게 입력해주세요." << endl;
        }
    }
    else {
        cout << "계좌번호를 올바르게 입력해주세요." << endl;
    }
}
void BankingSystem::showBalance() {
    if (currentUser.empty()) {
        cout << "먼저 로그인하세요!" << endl;
        return;
    }
    string accountNumber;
    cout << "잔액을 조회할 계좌번호를 입력하세요: "; cin >> accountNumber;
    User* user = userMap[currentUser].get();
    Account* account = user->getAccount(accountNumber);
    if (account) {
        account->showAccInfo();
    }
    else {
        cout << "계좌번호를 올바르게 입력해주세요." << endl;
    }
}
// void BankingSystem::showAllAccInfo() {
//     if (currentUser.empty()) {
//         cout << "먼저 로그인하세요!" << endl;
//         return;
//     }
//     if (curstate == 0) {
//         cout << "데이터를 먼저 불러오세요." << endl;
//         return;
//     }
// }

void BankingSystem::showAllAccInfo() {
    if (currentUser.empty()) {
        cout << "먼저 로그인하세요!" << endl;
        return;
    } 
    if (curstate == 0) {
        cout << "데이터를 먼저 불러오세요." << endl;
        return;
    }

    userMap[currentUser]->showAllAccounts();
}

void BankingSystem::saveData() {
    ofstream outFile("accountData.txt");
    if (!outFile) {
        cout << "파일 열기 실패" << endl;
        return;
    }
    for (const auto& pair : userMap) {
        outFile << pair.first << '\n';
        pair.second->saveAccounts(outFile);
    }
    cout << "데이터 저장을 완료했습니다." << endl;
}
void BankingSystem::loadData() {
    curstate = 0;
    ifstream inFile("accountData.txt"); // 유저별로 하나만 저장이 됌.
    if (!inFile) {
        cout << "파일 열기 실패" << endl;
        return;
    }
    userMap.clear();
    string userName;
    while (inFile >> userName) {
        userMap[userName] = make_unique<User>(userName);
        userMap[userName]->loadAccounts(inFile);
        curstate = 1;
    }
    cout << "데이터 불러오기를 완료했습니다." << endl;
}
void BankingSystem::finish() {
    saveData();
    cout << "프로그램을 종료합니다." << endl;
    exit(0);
}