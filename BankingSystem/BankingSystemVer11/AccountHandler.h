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
	int ShowMenu() const;			// 메뉴 출력
	void MakeAccount();				// 1. 계좌개설
	void DepositMoney();			// 2. 입금
	void WithdrawMoney();			// 3. 출금
	void ShowAllAccInfo() const;	// 4. 계좌정보 전체 출력
protected:
	void MakeNormalAccount();
	void MakeCreditAccount();
};