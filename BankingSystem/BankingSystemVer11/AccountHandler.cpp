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
	cout << "1. ���°���" << endl;
	cout << "2. �Ա�" << endl;
	cout << "3. ���" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
	cout << "���� : ";
	cin >> nSelect;
	cout << endl;

	return nSelect;
}

void AccountHandler::MakeAccount()
{
	int accType;

	cout << "[������������]" << endl;
	cout << "1. ���뿹�ݰ���  2. �ſ�ŷڰ���" << endl;
	cout << "���� : ";
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
		cout << "���� ������ �߸� �����ϼ̽��ϴ�." << endl << endl;
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
			cout << "[���뿹�ݰ��� ����]" << endl;
			cout << "����ID : ";
			cin >> accID;
			cout << "�̸� : ";
			cin >> cusName;
			cout << "�Աݾ� : ";
			cin >> balance;
			cout << "������ : ";
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
			cout << "[�ſ�ŷڰ��� ����]" << endl;
			cout << "����ID : ";
			cin >> accID;
			cout << "�̸� : ";
			cin >> cusName;
			cout << "�Աݾ� : ";
			cin >> balance;
			cout << "������ : ";
			cin >> rate;
			cout << "�ſ���(1toA, 2toB, 3toC) : ";
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
			cout << "[�Ա�]" << endl;
			cout << "����ID : ";
			cin >> accID;
			cout << "�Աݾ� : ";
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
					cout << "�ԱݿϷ�" << endl << endl;
					return;
				}
			}

			cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
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
			cout << "[���]" << endl;
			cout << "����ID : ";
			cin >> accID;
			cout << "��ݾ� : ";
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

					cout << "��ݿϷ�" << endl << endl;
					return;
				}
			}

			cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
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