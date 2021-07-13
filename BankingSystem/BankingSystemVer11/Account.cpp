#include "BankingCommonDecl.h"
#include "Account.h"
#include "AccountException.h"

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
	if (money < 0)
		throw MinusException(money);

	balance += money;
}

int Account::Withdraw(int money)		// ��ݾ� ��ȯ, ������ 0 ��ȯ
{
	if (money < 0)
		throw MinusException(money);

	if (balance < money)
		throw InsuffException(balance, money);

	balance -= money;

	return money;
}

void Account::ShowAccInfo() const
{
	cout << "����ID : " << accID << endl;
	cout << "�̸� : " << cusName << endl;
	cout << "�Աݾ� : " << balance << endl << endl;
}