/*
* Banking System Ver 0.5.0
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

class Account
{
private:
	int accID;				// ���¹�ȣ
	int balance;			// �ܾ�
	char *cusName;			// ���̸�
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

	int Withdraw(int money)		// ��ݾ� ��ȯ, ������ 0 ��ȯ
	{
		if (balance < money)
			return 0;

		balance -= money;

		return money;
	}

	void GetAccInfo() const
	{
		cout << "����ID : " << accID << endl;
		cout << "�̸� : " << cusName << endl;
		cout << "�Աݾ� : " << balance << endl << endl;
	}
};

class AccountHandler
{
private:
	Account *accArr[100];
	int acc_cnt;
public:
	AccountHandler() : acc_cnt(0)
	{
	}
	~AccountHandler()
	{
		for (int i = 0; i < acc_cnt; i++)
			delete accArr[i];
	}
	int ShowMenu();				// �޴� ���
	void MakeAccount();			// 1. ���°���
	void DepositMoney();		// 2. �Ա�
	void WithdrawMoney();		// 3. ���
	void ShowAllAccInfo();		// 4. �������� ��ü ���
};

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

int AccountHandler::ShowMenu()
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
	int accID;
	int balance;
	char cusName[NAME_LEN];

	cout << "[���°���]" << endl;
	cout << "����ID : ";
	cin >> accID;
	cout << "�̸� : ";
	cin >> cusName;
	cout << "�Աݾ� : ";
	cin >> balance;
	cout << endl;

	accArr[acc_cnt] = new Account(accID, balance, cusName);

	acc_cnt += 1;
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

void AccountHandler::ShowAllAccInfo()
{
	for (int i = 0; i < acc_cnt; i++)
	{
		accArr[i]->GetAccInfo();
	}
}