#pragma once
#include "Account.h"

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