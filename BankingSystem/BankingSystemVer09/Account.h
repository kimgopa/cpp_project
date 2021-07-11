#pragma once
#include "String.h"

class Account
{
private:
	int accID;				// °èÁÂ¹øÈ£
	int balance;			// ÀÜ¾×
	String cusName;			// °í°´ÀÌ¸§
public:
	Account(int _accID, int _balance, String _cusName);
	
	int GetAccID() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
};