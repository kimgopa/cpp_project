#pragma once
#include "Account.h"
#include "BoundCheckArray.h"

class AccountHandler
{
private:
	BoundCheckArray<Account*> accArr;
	int acc_cnt;
public:
	AccountHandler();
	~AccountHandler();
	int ShowMenu() const;			// �޴� ���
	void MakeAccount();				// 1. ���°���
	void DepositMoney();			// 2. �Ա�
	void WithdrawMoney();			// 3. ���
	void ShowAllAccInfo() const;	// 4. �������� ��ü ���
protected:
	void MakeNormalAccount();
	void MakeCreditAccount();
};