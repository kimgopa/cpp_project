#pragma once

class Account
{
private:
	int accID;				// °èÁÂ¹øÈ£
	int balance;			// ÀÜ¾×
	char *cusName;			// °í°´ÀÌ¸§
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