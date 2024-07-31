#include <iostream> // 입출력을 위한 헤더 파일
#include <vector> // 벡터 사용을 위한 헤더 파일
#include <memory> // 스마트 포인터 사용을 위한 헤더 파일
#include <fstream> // 파일 입출력을 위한 헤더 파일
#include <string> // 문자열 처리를 위한 헤더 파일
#include <unordered_map> // 해시 맵 사용을 위한 헤더 파일

using namespace std; // 표준 네임스페이스 사용

// 예외 처리를 위한 클래스
class BankingException : public exception {
public:
    void showExceptionLog() const { // 예외 로그를 출력하는 함수
        cout << "Banking exception occurred!" << endl;
    }
};

// 계좌의 기본 클래스
class Account {
protected:
    string accountNumber; // 계좌 번호
    string name; // 고객 이름
    int balance; // 잔액
public:
    Account(const string& accNum, const string& nm, int bal) // 계좌 생성자
        : accountNumber(accNum), name(nm), balance(bal) {}
    virtual ~Account() {} // 가상 소멸자

    string getName() const { // 고객 이름을 반환하는 함수
        return name;
    }

    virtual bool deposit(int money) { // 입금 함수
        if (money <= 0) return false; // 입금 금액이 0 이하이면 실패
        balance += money; // 잔액에 입금 금액 추가
        return true;
    }

    virtual bool withdraw(int money) { // 출금 함수
        if (money > balance || money <= 0) return false; // 출금 금액이 잔액보다 많거나 0 이하이면 실패
        balance -= money; // 잔액에서 출금 금액 차감
        return true;
    }

    virtual void showAccInfo() const { // 계좌 정보를 출력하는 함수
        cout << "계좌번호: " << accountNumber << ", 고객명: " << name << ", 잔액: " << balance << endl;
    }

    virtual void save(ofstream& outFile) const { // 계좌 정보를 파일에 저장하는 함수
        outFile << accountNumber << ' ' << name << ' ' << balance << '\n';
    }

    virtual void load(ifstream& inFile) { // 파일에서 계좌 정보를 읽어오는 함수
        inFile >> accountNumber >> name >> balance;
    }
};

// 보통 예금 계좌 클래스
class NormalAccount : public Account {
public:
    NormalAccount(const string& accNum, const string& nm, int bal) // 보통 예금 계좌 생성자
        : Account(accNum, nm, bal) {}

    void showAccInfo() const override { // 계좌 정보를 출력하는 함수
        cout << "[보통예금계좌] ";
        Account::showAccInfo();
    }

    void save(ofstream& outFile) const override { // 계좌 정보를 파일에 저장하는 함수
        outFile << "N ";
        Account::save(outFile);
    }
};

// 은행 시스템 관리 클래스
class BankingSystem {
    unordered_map<string, unique_ptr<Account>> accountMap; // 계좌 목록을 관리하는 해시 맵
    string currentUser; // 현재 사용자
public:
    void showMenu() { // 메뉴를 출력하는 함수
        system("cls"); // 콘솔 화면 지우기
        cout << "***** [Banking System] *****" << endl;
        cout << "1. 사용자 로그인" << endl;
        cout << "2. 계 좌  개 설" << endl;
        cout << "3. 입        금" << endl;
        cout << "4. 출        금" << endl;
        cout << "5. 잔 액  조 회" << endl;
        cout << "6. 모든계좌조회" << endl;
        cout << "7. 데이터저장" << endl;
        cout << "8. 데이터불러오기" << endl;
        cout << "9. 프로그램종료" << endl;
        cout << "이용할 기능을 입력하세요 : ";
    }

    void userLogin() { // 사용자 로그인 함수
        cout << "사용자 이름을 입력하세요: ";
        cin >> currentUser;
        cout << currentUser << "님 환영합니다!" << endl;
    }

    void makeAccount() { // 계좌 개설 함수
        if (currentUser.empty()) { // 로그인 여부 확인
            cout << "먼저 로그인하세요!" << endl;
            return;
        }
        int choice;
        cout << "1. 보통예금계좌" << endl;
        cout << "개설하실 계좌를 선택하세요 : ";
        cin >> choice;
        cout << endl;
        switch (choice) {
        case 1: // 보통 예금 계좌 개설
            makeNormalAccount();
            break;
        default: // 잘못된 선택
            cout << "잘못된 선택입니다." << endl;
            break;
        }
    }

    void makeNormalAccount() { // 보통 예금 계좌 개설 함수
        string accountNumber, name;
        int money;
        cout << "[보통예금계좌]" << endl;
        cout << "계좌번호: "; cin >> accountNumber;
        cout << "고객명: "; cin >> name;
        cout << "입금하실 금액: "; cin >> money;
        accountMap[accountNumber] = make_unique<NormalAccount>(accountNumber, name, money);
        cout << "계좌 개설을 성공했습니다." << endl;
    }

    void deposit() { // 입금 함수
        if (currentUser.empty()) { // 로그인 여부 확인
            cout << "먼저 로그인하세요!" << endl;
            return;
        }
        if (accountMap.empty()) { // 계좌 개설 여부 확인
            cout << "개설된 계좌가 없습니다." << endl;
            return;
        }
        string accountNumber;
        int money;
        cout << "입금하실 계좌번호를 입력하세요: "; cin >> accountNumber;
        cout << "금액: "; cin >> money;
        try {
            if (accountMap.count(accountNumber)) { // 계좌 존재 여부 확인
                if (accountMap[accountNumber]->deposit(money)) { // 입금 시도
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
        catch (BankingException& expn) { // 예외 처리
            expn.showExceptionLog();
        }
    }

    void withdraw() { // 출금 함수
        if (currentUser.empty()) { // 로그인 여부 확인
            cout << "먼저 로그인하세요!" << endl;
            return;
        }
        if (accountMap.empty()) { // 계좌 개설 여부 확인
            cout << "개설된 계좌가 없습니다." << endl;
            return;
        }
        string accountNumber;
        int money;
        cout << "출금하실 계좌번호를 입력하세요: "; cin >> accountNumber;
        cout << "금액: "; cin >> money;
        try {
            if (accountMap.count(accountNumber)) { // 계좌 존재 여부 확인
                if (accountMap[accountNumber]->withdraw(money)) { // 출금 시도
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
        catch (BankingException& expn) { // 예외 처리
            expn.showExceptionLog();
        }
    }

    void showBalance() { // 잔액 조회 함수
    
        if (currentUser.empty()) { // 로그인 여부 확인
            cout << "먼저 로그인하세요!" << endl;
            return;
        }
        if (accountMap.empty()) { // 계좌 개설 여부 확인
            cout << "개설된 계좌가 없습니다." << endl;
            return;
        }
        string accountNumber;
        cout << "잔액을 조회할 계좌번호를 입력하세요: "; cin >> accountNumber;
        if (accountMap.count(accountNumber)) { // 계좌 존재 여부 확인
            accountMap[accountNumber]->showAccInfo(); // 잔액 출력
        }
        else {
            cout << "계좌번호를 올바르게 입력해주세요." << endl;
        }
    }

    void showAllAccInfo() { // 모든 계좌 정보 출력 함수
        if (currentUser.empty()) { // 로그인 여부 확인
            cout << "먼저 로그인하세요!" << endl;
            return;
        }
        if (accountMap.empty()) { // 계좌 개설 여부 확인
            cout << "개설된 계좌가 없습니다." << endl;
            return;
        }
        for (const auto& pair : accountMap) { // 모든 계좌 정보 출력
            pair.second->showAccInfo();
        }
        cout << "총 " << accountMap.size() << "건이 조회됐습니다." << endl;
    }

    void saveData() { // 데이터 저장 함수
        ofstream outFile("accountData.txt"); // 파일 열기
        if (!outFile) { // 파일 열기 실패 시
            cout << "파일 열기 실패" << endl;
            return;
        }
        for (const auto& pair : accountMap) { // 모든 계좌 정보 파일에 저장
            pair.second->save(outFile);
        }
        cout << "데이터 저장을 완료했습니다." << endl;
    }

    void loadData() { // 데이터 불러오기 함수
        ifstream inFile("accountData.txt"); // 파일 열기
        if (!inFile) { // 파일 열기 실패 시
            cout << "파일 열기 실패" << endl;
            return;
        }
        accountMap.clear(); // 기존 데이터 초기화
        char accountType;
        while (inFile >> accountType) { // 파일에서 계좌 정보 읽어오기
            string accountNumber, name;
            int balance;
            if (accountType == 'N') { // 보통 예금 계좌
                inFile >> accountNumber >> name >> balance;
                accountMap[accountNumber] = make_unique<NormalAccount>(accountNumber, name, balance);
            }
        }
        cout << "데이터 불러오기를 완료했습니다." << endl;
    }

    void finish() { // 프로그램 종료 함수
        saveData(); // 데이터 저장
        cout << "프로그램을 종료합니다." << endl;
        exit(0); // 프로그램 종료
    }
};

int main() {
    BankingSystem bsHandler; // 은행 시스템 객체 생성
    int choice;
    while (true) {
        bsHandler.showMenu(); // 메뉴 출력
        cin >> choice;
        switch (choice) {
        case 1:
            bsHandler.userLogin(); // 사용자 로그인
            break;
        case 2:
            bsHandler.makeAccount(); // 계좌 개설
            break;
        case 3:
            bsHandler.deposit(); // 입금
            break;
        case 4:
            bsHandler.withdraw(); // 출금
            break;
        case 5:
            bsHandler.showBalance(); // 잔액 조회
            break;
        case 6:
            bsHandler.showAllAccInfo(); // 모든 계좌 정보 조회
            break;
        case 7:
            bsHandler.saveData(); // 데이터 저장
            break;
        case 8:
            bsHandler.loadData(); // 데이터 불러오기
            break;
        case 9:
            bsHandler.finish(); // 프로그램 종료
            break;
        default:
            continue;
        }
        cout << "Press any key to continue...";
        cin.ignore();
        cin.get();
    }
    return 0;
}
