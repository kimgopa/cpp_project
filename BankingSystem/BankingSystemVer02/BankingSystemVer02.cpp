/*
* Banking System Ver 0.2.0
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Account
{
private:
	int		accID;				// ���¹�ȣ
	int		balance;			// �ܾ�
	char	*cusName;			// ���̸�
public:
	Account(int _accID, int _balance, char *_cusName)
	{
		accID = _accID;
		balance = _balance;
		cusName = new char[strlen(_cusName) + 1];
		strcpy(cusName, _cusName);
	}
	~Account()
	{
		delete[] cusName;
	}
	int GetAccID() const
	{
		return accID;
	}
	void SetBalance(int _balance)
	{
		balance += _balance;
	}
	void GetAccInfo() const
	{
		cout << "����ID : " << accID << endl;
		cout << "�̸� : " << cusName << endl;
		cout << "�Աݾ� : " << balance << endl;
		cout << endl;
	}
};

int ShowMenu();				// �޴� ���
void MakeAccount();			// 1. ���°���
void DepositMoney();		// 2. �Ա�
void WithdrawMoney();		// 3. ���
void ShowAllAccInfo();		// 4. �������� ��ü ���

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

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

void MakeAccount()
{
	int accID;
	int balance;
	char cusName[100];

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

void DepositMoney()
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
			accArr[i]->SetBalance(money);
			cout << "�ԱݿϷ�" << endl << endl;
			return;
		}
	}

	cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
}

void WithdrawMoney()
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
			accArr[i]->SetBalance(-money);
			cout << "��ݿϷ�" << endl << endl;
			return;
		}
	}

	cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
}

void ShowAllAccInfo()
{
	for (int i = 0; i < acc_cnt; i++)
	{
		accArr[i]->GetAccInfo();
	}
}