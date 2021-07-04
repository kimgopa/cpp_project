/*
* Banking System Ver 0.6.1
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

// �޴�
enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

// �ſ���
enum { LEVEL_A = 7, LEVEL_B = 4, LEVEL_C = 2 };

// ���� ����
enum { NORMAL = 1, CREDIT = 2 };

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

class NormalAccount : public Account	// ���뿹�ݰ���
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

class HighCreditAccount : public NormalAccount	// �ſ�ŷڰ���
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
	int ShowMenu() const;			// �޴� ���
	void MakeAccount();				// 1. ���°���
	void DepositMoney();			// 2. �Ա�
	void WithdrawMoney();			// 3. ���
	void ShowAllAccInfo() const;	// 4. �������� ��ü ���
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