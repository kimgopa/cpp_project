#pragma once
#include <iostream>
#include "NormalAccount.h"

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