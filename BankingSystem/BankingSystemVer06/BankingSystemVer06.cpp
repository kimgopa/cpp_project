/*
* Banking System Ver 0.6.1
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

// 메뉴
enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

// 신용등급
enum { LEVEL_A = 7, LEVEL_B = 4, LEVEL_C = 2 };

// 계좌 종류
enum { NORMAL = 1, CREDIT = 2 };

class Account
{
private:
	int accID;				// 계좌번호
	int balance;			// 잔액
	char *cusName;			// 고객이름
public:
	Account(int _accID, int _balance, char *_cusName);
	Account(const Account &copy);
	~Account();
	int GetAccID() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
};

Account::Account(int _accID, int _balance, char *_cusName) : accID(_accID), balance(_balance)
{
	cusName = new char[strlen(_cusName) + 1];
	strcpy(cusName, _cusName);
}

Account::Account(const Account &copy) : accID(copy.accID), balance(copy.balance)
{
	cusName = new char[strlen(copy.cusName) + 1];
	strcpy(cusName, copy.cusName);
}

Account::~Account()
{
	delete[] cusName;
}

int Account::GetAccID() const
{
	return accID;
}

void Account::Deposit(int money)
{
	balance += money;
}

int Account::Withdraw(int money)		// 출금액 반환, 부족시 0 반환
{
	if (balance < money)
		return 0;

	balance -= money;

	return money;
}

void Account::ShowAccInfo() const
{
	cout << "계좌ID : " << accID << endl;
	cout << "이름 : " << cusName << endl;
	cout << "입금액 : " << balance << endl << endl;
}

class NormalAccount : public Account	// 보통예금계좌
{
private:
	int rate;
public:
	NormalAccount(int _accID, int _balance, char *_cusName, int _rate);
	void Deposit(int money);
};

NormalAccount::NormalAccount(int _accID, int _balance, char *_cusName, int _rate)
	: Account(_accID, _balance, _cusName), rate(_rate)
{
}

void NormalAccount::Deposit(int money)
{
	Account::Deposit(money);
	Account::Deposit(money * (rate / 100.0));
}

class HighCreditAccount : public NormalAccount	// 신용신뢰계좌
{
private:
	int level;
public:
	HighCreditAccount(int _accID, int _balance, char *_cusName, int _rate, int _level);
	void Deposit(int money);
};

HighCreditAccount::HighCreditAccount(int _accID, int _balance, char *_cusName, int _rate, int _level)
	: NormalAccount(_accID, _balance, _cusName, _rate), level(_level)
{
}

void HighCreditAccount::Deposit(int money)
{
	NormalAccount::Deposit(money);
	Account::Deposit(money * (level / 100.0));
}

class AccountHandler
{
private:
	Account *accArr[100];
	int acc_cnt;
public:
	AccountHandler();
	~AccountHandler();
	int ShowMenu() const;			// 메뉴 출력
	void MakeAccount();				// 1. 계좌개설
	void DepositMoney();			// 2. 입금
	void WithdrawMoney();			// 3. 출금
	void ShowAllAccInfo() const;	// 4. 계좌정보 전체 출력
protected:
	void MakeNormalAccount();
	void MakeCreditAccount();
};

AccountHandler::AccountHandler() : acc_cnt(0)
{
}

AccountHandler::~AccountHandler()
{
	for (int i = 0; i < acc_cnt; i++)
		delete accArr[i];
}

int AccountHandler::ShowMenu() const
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

void AccountHandler::MakeAccount()
{
	int accType;

	cout << "[계좌종류선택]" << endl;
	cout << "1. 보통예금계좌  2. 신용신뢰계좌" << endl;
	cout << "선택 : ";
	cin >> accType;
	
	switch (accType)
	{
	case NORMAL:
		MakeNormalAccount();
		break;
	case CREDIT:
		MakeCreditAccount();
		break;
	default:
		cout << "계좌 종류를 잘못 선택하셨습니다." << endl << endl;
		break;
	}
}

void AccountHandler::MakeNormalAccount()
{
	int accID;
	int balance;
	char cusName[NAME_LEN];
	int rate;

	cout << "[보통예금계좌 개설]" << endl;
	cout << "계좌ID : ";
	cin >> accID;
	cout << "이름 : ";
	cin >> cusName;
	cout << "입금액 : ";
	cin >> balance;
	cout << "이자율 : ";
	cin >> rate;
	cout << endl;
	accArr[acc_cnt] = new NormalAccount(accID, balance, cusName, rate);
	acc_cnt += 1;
}

void AccountHandler::MakeCreditAccount()
{
	int accID;
	int balance;
	char cusName[NAME_LEN];
	int rate;
	int level;

	cout << "[신용신뢰계좌 개설]" << endl;
	cout << "계좌ID : ";
	cin >> accID;
	cout << "이름 : ";
	cin >> cusName;
	cout << "입금액 : ";
	cin >> balance;
	cout << "이자율 : ";
	cin >> rate;
	cout << "신용등급(1toA, 2toB, 3toC) : ";
	cin >> level;
	cout << endl;

	switch (level)
	{
	case 1:
		accArr[acc_cnt] = new HighCreditAccount(accID, balance, cusName, rate, LEVEL_A);
		acc_cnt += 1;
		break;
	case 2:
		accArr[acc_cnt] = new HighCreditAccount(accID, balance, cusName, rate, LEVEL_B);
		acc_cnt += 1;
		break;
	case 3:
		accArr[acc_cnt] = new HighCreditAccount(accID, balance, cusName, rate, LEVEL_C);
		acc_cnt += 1;
		break;
	}
}

void AccountHandler::DepositMoney()
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

void AccountHandler::WithdrawMoney()
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

void AccountHandler::ShowAllAccInfo() const
{
	for (int i = 0; i < acc_cnt; i++)
	{
		accArr[i]->ShowAccInfo();
	}
}

int main(void)
{
	AccountHandler handler;

	while (1)
	{
		switch (handler.ShowMenu())
		{
		case MAKE:
			handler.MakeAccount();
			break;
		case DEPOSIT:
			handler.DepositMoney();
			break;
		case WITHDRAW:
			handler.WithdrawMoney();
			break;
		case INQUIRE:
			handler.ShowAllAccInfo();
			break;
		case EXIT:
			return 0;
		default:
			cout << "Illegal selection." << endl << endl;
		}
	}

	return 0;
}