#pragma once
#include "String.h"

class Account
{
private:
	int accID;				// ���¹�ȣ
	int balance;			// �ܾ�
	String cusName;			// ���̸�
public:
	Account(int _accID, int _balance, String _cusName);
	
	int GetAccID() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
};