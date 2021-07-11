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

void AccountHandler::MakeNormalAccount()
{
	int accID;
	int balance;
	char cusName[NAME_LEN];
	int rate;

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

	cout << "[�Ա�]" << endl;
	cout << "����ID : ";
	cin >> accID;
	cout << "�Աݾ� : ";
	cin >> money;

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

void AccountHandler::WithdrawMoney()
{
	int accID;
	int money;

	cout << "[���]" << endl;
	cout << "����ID : ";
	cin >> accID;
	cout << "��ݾ� : ";
	cin >> money;

	for (int i = 0; i < acc_cnt; i++)
	{
		if (accArr[i]->GetAccID() == accID)
		{
			if (accArr[i]->Withdraw(money) == 0)
			{
				cout << "�ܾ׺���" << endl << endl;
				return;
			}

			cout << "��ݿϷ�" << endl << endl;
			return;
		}
	}

	cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
}

void AccountHandler::ShowAllAccInfo() const
{
	for (int i = 0; i < acc_cnt; i++)
	{
		accArr[i]->ShowAccInfo();
	}
}