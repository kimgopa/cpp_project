#include "BankingCommonDecl.h"
#include "Account.h"

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

Account &Account::operator=(const Account &ref)
{
	accID = ref.accID;
	balance = ref.balance;

	delete[] cusName;
	cusName = new char[strlen(ref.cusName) + 1];
	strcpy(cusName, ref.cusName);
	return *this;
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