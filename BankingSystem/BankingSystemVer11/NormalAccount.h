#pragma once
#include "Account.h"
#include "String.h"

class NormalAccount : public Account	// 보통예금계좌
{
private:
	int rate;
public:
	NormalAccount(int _accID, int _balance, String _cusName, int _rate)
		: Account(_accID, _balance, _cusName), rate(_rate) {}
	virtual void Deposit(int money)
	{
		Account::Deposit(money);
		Account::Deposit(money * (rate / 100.0));
	}
};