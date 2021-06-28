/*
* Banking System Ver 0.3.0
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

int ShowMenu();				// 메뉴 출력
void MakeAccount();			// 1. 계좌개설
void DepositMoney();		// 2. 입금
void WithdrawMoney();		// 3. 출금
void ShowAllAccInfo();		// 4. 계좌정보 전체 출력

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

class Account
{
private:
	int		accID;				// 계좌번호
	int		balance;			// 잔액
	char *cusName;			// 고객이름
public:
	Account(int _accID, int _balance, char *_cusName) : accID(_accID), balance(_balance)
	{
		cusName = new char[strlen(_cusName) + 1];
		strcpy(cusName, _cusName);
	}

	Account(const Account &copy) : accID(copy.accID), balance(copy.balance)
	{
		cusName = new char[strlen(copy.cusName) + 1];
		strcpy(cusName, copy.cusName);
	}

	~Account()
	{
		delete[] cusName;
	}

	int GetAccID() const
	{
		return accID;
	}

	void Deposit(int money)
	{
		balance += money;
	}

	int Withdraw(int money)		// 출금액 반환, 부족시 0 반환
	{
		if (balance < money)
			return 0;

		balance -= money;

		return money;
	}

	void GetAccInfo() const
	{
		cout << "계좌ID : " << accID << endl;
		cout << "이름 : " << cusName << endl;
		cout << "입금액 : " << balance << endl << endl;
	}
};

Account *accArr[100];
int acc_cnt = 0;

int main(void)
{
	while (1)
	{
		switch (ShowMenu())
		{
		case MAKE:
			MakeAccount();
			break;
		case DEPOSIT:
			DepositMoney();
			break;
		case WITHDRAW:
			WithdrawMoney();
			break;
		case INQUIRE:
			ShowAllAccInfo();
			break;
		case EXIT:
			for (int i = 0; i < acc_cnt; i++)
				delete accArr[i];
			return 0;
		default:
			cout << "Illegal selection." << endl << endl;
		}
	}

	return 0;
}

int ShowMenu()
{
	int nSelect;
	cout << "------ Menu -----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입금" << endl;
	cout << "3. 출금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
	cout << "선택 : ";
	cin >> nSelect;
	cout << endl;

	return nSelect;
}

void MakeAccount()
{
	int accID;
	int balance;
	char cusName[NAME_LEN];

	cout << "[계좌개설]" << endl;
	cout << "계좌ID : ";
	cin >> accID;
	cout << "이름 : ";
	cin >> cusName;
	cout << "입금액 : ";
	cin >> balance;
	cout << endl;

	accArr[acc_cnt] = new Account(accID, balance, cusName);

	acc_cnt += 1;
}

void DepositMoney()
{
	int accID;
	int money;

	cout << "[입금]" << endl;
	cout << "계좌ID : ";
	cin >> accID;
	cout << "입금액 : ";
	cin >> money;

	for (int i = 0; i < acc_cnt; i++)
	{
		if (accArr[i]->GetAccID() == accID)
		{
			accArr[i]->Deposit(money);
			cout << "입금완료" << endl << endl;
			return;
		}
	}

	cout << "유효하지 않은 ID입니다." << endl << endl;
}

void WithdrawMoney()
{
	int accID;
	int money;

	cout << "[출금]" << endl;
	cout << "계좌ID : ";
	cin >> accID;
	cout << "출금액 : ";
	cin >> money;

	for (int i = 0; i < acc_cnt; i++)
	{
		if (accArr[i]->GetAccID() == accID)
		{
			if (accArr[i]->Withdraw(money) == 0)
			{
				cout << "잔액부족" << endl << endl;
				return;
			}

			cout << "출금완료" << endl << endl;
			return;
		}
	}

	cout << "유효하지 않은 ID입니다." << endl << endl;
}

void ShowAllAccInfo()
{
	for (int i = 0; i < acc_cnt; i++)
	{
		accArr[i]->GetAccInfo();
	}
}