#pragma once
#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "User.h"

using namespace std;

class BankingSystem {
    map<string, unique_ptr<User>> userMap;
    vector <Account*> acc;
    string currentUser; // 현재 사용자
    int curstate;
public:
    
    bool userLogin();           // 사용자 로그인 함수
    void makeAccount();         // 계좌 개설 함수
    void makeNormalAccount();   // 보통 예끔 계좌 개설 함수
    void deposit();             // 입금 함수
    void withdraw();            // 출금 함수
    void showBalance();         // 잔액 조회 함수
    void showAllAccInfo();      // 모든 계좌 정보 출력 함수
    void saveData();            // 데이터 저장 함수
    void loadData();            // 기존 데이터 불러오기
    void finish();              // 프로그램 종료
};

#endif // BANKINGSYSTEM_H