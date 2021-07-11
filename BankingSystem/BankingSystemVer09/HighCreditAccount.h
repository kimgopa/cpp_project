#pragma once
#include "NormalAccount.h"
#include "String.h"

class HighCreditAccount : public NormalAccount	// ½Å¿ë½Å·Ú°èÁÂ
{
private:
	int level;
public:
	HighCreditAccount(int _accID, int _balance, String _cusName, int _rate, int _level)
		: NormalAccount(_accID, _balance, _cusName, _rate), level(_level) {}
	virtual void Deposit(int money)
	{
		NormalAccount::Deposit(money);
		Account::Deposit(money * (level / 100.0));
	}
};