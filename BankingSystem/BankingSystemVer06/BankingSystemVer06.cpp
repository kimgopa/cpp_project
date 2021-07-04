/*
* Banking System Ver 0.6.0
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

namespace CREDIT_LEVEL
{
	enum { LEVEL_A = 1, LEVEL_B = 2, LEVEL_C = 3 };
	enum { LEVEL_A_RATIO = 7, LEVEL_B_RATIO = 4, LEVEL_C_RATIO = 2 };
}

class Account
{
private:
	int accID;				// ���¹�ȣ
	int balance;			// �ܾ�
	char *cusName;			// ���̸�
public:
	Account(int _accID, int _balance, char *_cusName);
	Account(const Account &copy);
	~Account();
	int GetAccID() const;
	int GetBalance() const;
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

int Account::GetBalance() const
{
	return balance;
}

void Account::Deposit(int money)
{
	balance += money;
}

int Account::Withdraw(int money)		// ��ݾ� ��ȯ, ������ 0 ��ȯ
{
	if (balance < money)
		return 0;

	balance -= money;

	return money;
}

void Account::ShowAccInfo() const
{
	cout << "����ID : " << accID << endl;
	cout << "�̸� : " << cusName << endl;
	cout << "�Աݾ� : " << balance << endl << endl;
}

class NormalAccount : public Account		// ���뿹�ݰ���
{
private:
	double ratio;
public:
	NormalAccount(int _accID, int _balance, char *_cusName, int _ratio);
	void Deposit(int money);
};

NormalAccount::NormalAccount(int _accID, int _balance, char *_cusName, int _ratio)
	: Account(_accID, _balance, _cusName), ratio(_ratio)
{
}

void NormalAccount::Deposit(int money)
{
	money += (int)(GetBalance() * (ratio / 100));
	Account::Deposit(money);
}

class HighCreditAccount : public Account	// �ſ�ŷڰ���
{
private:
	double ratio;
	int level;
public:
	HighCreditAccount(int _accID, int _balance, char *_cusName, int _ratio, int _level);
	void Deposit(int money);
};

HighCreditAccount::HighCreditAccount(int _accID, int _balance, char *_cusName, int _ratio, int _level)
	: Account(_accID, _balance, _cusName), ratio(_ratio), level(_level)
{
}

void HighCreditAccount::Deposit(int money)
{
	switch (level)
	{
	case CREDIT_LEVEL::LEVEL_A:
		money += (int)(GetBalance() * ((CREDIT_LEVEL::LEVEL_A_RATIO + ratio) / 100));
		break;
	case CREDIT_LEVEL::LEVEL_B:
		money += (int)(GetBalance() * ((CREDIT_LEVEL::LEVEL_B_RATIO + ratio) / 100));
		break;
	case CREDIT_LEVEL::LEVEL_C:
		money += (int)(GetBalance() * ((CREDIT_LEVEL::LEVEL_C_RATIO + ratio) / 100));
		break;
	}
	Account::Deposit(money);
}

class AccountHandler
{
private:
	Account *accArr[100];
	int acc_cnt;
public:
	AccountHandler();
	~AccountHandler();
	int ShowMenu() const;			// �޴� ���
	void MakeAccount();				// 1. ���°���
	void DepositMoney();			// 2. �Ա�
	void WithdrawMoney();			// 3. ���
	void ShowAllAccInfo() const;	// 4. �������� ��ü ���
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
	int accID;
	int balance;
	char cusName[NAME_LEN];
	int ratio;
	int level;

	cout << "[������������]" << endl;
	cout << "1. ���뿹�ݰ���  2. �ſ�ŷڰ���" << endl;
	cout << "���� : ";
	cin >> accType;
	
	switch (accType)
	{
	case 1 :
		cout << "[���뿹�ݰ��� ����]" << endl;
		cout << "����ID : ";
		cin >> accID;
		cout << "�̸� : ";
		cin >> cusName;
		cout << "�Աݾ� : ";
		cin >> balance;
		cout << "������ : ";
		cin >> ratio;
		cout << endl;
		accArr[acc_cnt] = new NormalAccount(accID, balance, cusName, ratio);
		acc_cnt += 1;
		break;
	case 2:
		cout << "[�ſ�ŷڰ��� ����]" << endl;
		cout << "����ID : ";
		cin >> accID;
		cout << "�̸� : ";
		cin >> cusName;
		cout << "�Աݾ� : ";
		cin >> balance;
		cout << "������ : ";
		cin >> ratio;
		cout << "�ſ���(1toA, 2toB, 3toC) : ";
		cin >> level;
		cout << endl;
		accArr[acc_cnt] = new HighCreditAccount(accID, balance, cusName, ratio, level);
		acc_cnt += 1;
		break;
	default:
		cout << "���� ������ �߸� �����ϼ̽��ϴ�." << endl << endl;
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
