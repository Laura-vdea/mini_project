#include <iostream>
#include "BankingSystem.h"

// #include <cstdlib>

void startMenu() {
    // 윈도우는 system("cls");
    system("clear"); // 화면을 지우는 명령
    cout << "--BANK--\n";
    cout << "1. 로그인\n2. 종료\n";
    cout << "----";
}

void showMenu() {
    system("clear"); // 화면을 지우는 명령
    std::cout << "\n1. 계좌 개설" << std::endl;
    std::cout << "2. 입금" << std::endl;
    std::cout << "3. 출금" << std::endl;
    std::cout << "4. 잔액 조회" << std::endl;
    std::cout << "5. 계좌 조회" << std::endl;
    std::cout << "6. 데이터 저장" << std::endl;
    std::cout << "7. 데이터 불러오기" << std::endl;
    std::cout << "8. 프로그램 종료\n" << std::endl;
    std::cout << "이용할 기능을 입력하세요 : ";
}

int main() {
    BankingSystem bsHandler; // 은행 시스템 객체 생성
    int choice;

    while (true) {
        startMenu();
        int fchoice;
        std::cin >> fchoice;
        if (fchoice == 2) break;
        if (fchoice == 1) {
            if (bsHandler.userLogin()) {
                while (true) {
                    string line;
                    // 이렇게 메뉴출력해도 좋다.
                    // ifstream file("bankmenu.txt");
                    if (file.is_open()) {
                        while (getline(file, line)) {
                            std::cout << line << endl;
                        }
                        file.close();
                    }
                    else {
                        std::cout << "unable to open file";
                        return 1;
                    }
                    showMenu();
                    cin >> choice;

                    switch (choice) {
                        //case 1:
                        //    bsHandler.userLogin(); // 사용자 로그인
                        //    break;
                    case 1:
                        bsHandler.makeAccount(); // 계좌 개설
                        break;
                    case 2:
                        bsHandler.deposit(); // 입금
                        break;
                    case 3:
                        bsHandler.withdraw(); // 출금
                        break;
                    case 4:
                        bsHandler.showBalance(); // 잔액 조회
                        break;
                    case 5:
                        bsHandler.showAllAccInfo(); // 모든 계좌 정보 조회
                        break;
                    case 6:
                        bsHandler.saveData(); // 데이터 저장
                        break;
                    case 7:
                        bsHandler.loadData(); // 데이터 불러오기
                        break;
                    case 8:
                        bsHandler.finish(); // 프로그램 종료
                        break;
                    case -1:
                        bsHandler.finish(); // 프로그램 종료
                        break;
                    default:
                        continue;
                    }
                    std::cout << "Press any key to continue...";
                    std::cin.ignore();
                    std::cin.get();
                }
                
            }
            else
                std::cout<<"로그인 실패";
        }
        

    }
    return 0;
}
