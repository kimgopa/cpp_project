#include "BankingCommonDecl.h"
#include "AccountHandler.h"
#include "Account.h"
#include "NormalAccount.h"
#include "HighCreditAccount.h"
#include "String.h"
#include "Exception.h"

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

void AccountHandler::MakeNormalAccount() throw (Exception)
{
	int accID;
	int balance;
	String cusName;
	int rate;

	while (1)
	{
		try
		{
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

			if (balance < 0)
			{
				MinusException expn;
				throw expn;
			}

			accArr[acc_cnt] = new NormalAccount(accID, balance, cusName, rate);
			acc_cnt += 1;
			break;
		}
		catch (MinusException &expn)
		{
			expn.ShowExceptionReason();
		}
	}
}

void AccountHandler::MakeCreditAccount() throw (Exception)
{
	int accID;
	int balance;
	String cusName;
	int rate;
	int level;

	while (1)
	{
		try
		{
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

			if (balance < 0)
			{
				MinusException expn;
				throw expn;
			}

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

			break;
		}
		catch (MinusException &expn)
		{
			expn.ShowExceptionReason();
		}
	}
}

void AccountHandler::DepositMoney() throw (Exception)
{
	int accID;
	int money;

	while (1)
	{
		try
		{
			cout << "[입금]" << endl;
			cout << "계좌ID : ";
			cin >> accID;
			cout << "입금액 : ";
			cin >> money;

			if (money < 0)
			{
				MinusException expn;
				throw expn;
			}

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
		catch (MinusException &expn)
		{
			expn.ShowExceptionReason();
		}
	}
}

void AccountHandler::WithdrawMoney() throw (Exception)
{
	int accID;
	int money;

	while (1)
	{
		try
		{
			cout << "[출금]" << endl;
			cout << "계좌ID : ";
			cin >> accID;
			cout << "출금액 : ";
			cin >> money;

			if (money < 0)
			{
				MinusException expn1;
				throw expn1;
			}

			for (int i = 0; i < acc_cnt; i++)
			{
				if (accArr[i]->GetAccID() == accID)
				{
					if (accArr[i]->Withdraw(money) == 0)
					{
						WithdrawException expn2(money);
						throw expn2;
					}

					cout << "출금완료" << endl << endl;
					return;
				}
			}

			cout << "유효하지 않은 ID입니다." << endl << endl;
		}
		catch (MinusException &expn1)
		{
			expn1.ShowExceptionReason();
		}
		catch (WithdrawException &expn2)
		{
			expn2.ShowExceptionReason();
		}
	}
}

void AccountHandler::ShowAllAccInfo() const
{
	for (int i = 0; i < acc_cnt; i++)
	{
		accArr[i]->ShowAccInfo();
	}
}