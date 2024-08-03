#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Account {
protected:
    string accountNumber; // 계좌 번호
    string name; // 고객 이름
    int balance; // 잔액
public:
    // 계좌 생성자
    Account(const string& accNum, const string& nm, int bal)
        : accountNumber(accNum), name(nm), balance(bal) {}
    virtual ~Account() {}
    string getName() const;                 // 고객 이름을 반환하는 함수
    virtual bool deposit(int money);        // 입금 함수
    virtual bool withdraw(int money);       // 출금 함수
    virtual void showAccInfo() const;       // 계좌 정보를 출력하는 함수
    virtual void save(ofstream& outFile) const; // 계좌 정보를 파일에 저장하는 함수
    virtual void load(ifstream& inFile);    // 파일에서 계좌 정보를 읽어오는 함수
};

#endif // ACCOUNT_H