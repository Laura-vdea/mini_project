#include "NormalAccount.h"
#include "Account.h"

string Account::getName() const {
    return name;
}

bool Account::deposit(int money) {  // 입금 함수
    if (money <= 0) return false; // 입금 금액이 0 이하이면 실패
    balance += money; // 잔액에 입금 금액 추가
    return true;
}

bool Account::withdraw(int money) {  // 출금 함수
    if (money > balance || money <= 0) return false; // 출금 금액이 잔액보다 많거나 0 이하이면 실패
    balance -= money; // 잔액에서 출금 금액 차감
    return true;
}

void Account::showAccInfo() const {  // 계좌 정보를 출력하는 함수
    cout << "계좌번호: " << accountNumber << ", 고객명: " << name << ", 잔액: " << balance << endl;
}

void Account::save(ofstream& outFile) const {  // 계좌 정보를 파일에 저장하는 함수
    outFile << accountNumber << ' ' << name << ' ' << balance << '\n';
}

void Account::load(ifstream& inFile) {   // 파일에서 계좌 정보를 읽어오는 함수
    inFile >> accountNumber >> name >> balance;
}