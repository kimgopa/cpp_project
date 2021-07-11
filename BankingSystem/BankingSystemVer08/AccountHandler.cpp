#include "BankingCommonDecl.h"
#include "AccountHandler.h"
#include "Account.h"
#include "NormalAccount.h"
#include "HighCreditAccount.h"

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