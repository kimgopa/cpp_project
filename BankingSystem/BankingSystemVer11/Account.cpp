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

int Account::Withdraw(int money)		// 출금액 반환, 부족시 0 반환
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
	cout << "계좌ID : " << accID << endl;
	cout << "이름 : " << cusName << endl;
	cout << "입금액 : " << balance << endl << endl;
}