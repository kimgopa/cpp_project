#pragma once

class Account
{
private:
	int accID;				// ���¹�ȣ
	int balance;			// �ܾ�
	char *cusName;			// ���̸�
public:
	Account(int _accID, int _balance, char *_cusName);
	Account(const Account &copy);
	~Account();

	Account &operator=(const Account &ref);
	
	int GetAccID() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
};