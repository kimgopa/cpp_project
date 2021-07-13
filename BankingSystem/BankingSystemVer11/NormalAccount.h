#pragma once
#include "Account.h"
#include "String.h"
#include "AccountException.h"

class NormalAccount : public Account	// ���뿹�ݰ���
{
private:
	int rate;
public:
	NormalAccount(int _accID, int _balance, String _cusName, int _rate)
		: Account(_accID, _balance, _cusName), rate(_rate)
	{}
	virtual void Deposit(int money)
	{
		if (money < 0)
			throw MinusException(money);

		Account::Deposit(money);
		Account::Deposit(money * (rate / 100.0));
	}
};