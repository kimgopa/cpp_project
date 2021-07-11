#include "BankingCommonDecl.h"
#include "Account.h"

Account::Account(int _accID, int _balance, String _cusName) : accID(_accID), balance(_balance)
{
	cusName = _cusName;
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