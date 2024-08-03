#pragma once
#ifndef _BANKINGEXCEPTION_H
#define _BANKINGEXCEPTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>

using namespace std;

// 예외 처리를 위한 클래스
class BankingException : public exception {
public:
    void showExceptionLog() const { // 예외 로그를 출력하는 함수
        cout << "Banking exception occurred!" << endl;
    }
};

#endif