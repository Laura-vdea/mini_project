#pragma once
#ifndef _NORMALACCOUNT_H
#define _NORMALACCOUNT_H

#include "Account.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>

using namespace std;

class NormalAccount : public Account {
public:
    // 보통 예금 계좌 생성자
    NormalAccount(const string& accNum, const string& nm, int bal)
        : Account(accNum, nm, bal) {}
    void showAccInfo() const;           // 계좌 정보를 출력하는 함수
    void save(ofstream& outFile) const; // 계좌 정보를 파일에 저장하는 함수
};

#endif // _NORMALACCOUNT_H