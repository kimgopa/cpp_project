/*
* Banking System Ver 0.10.0
*/
#include "BankingCommonDecl.h"
#include "AccountHandler.h"

int main(void)
{
	AccountHandler handler;

	while (1)
	{
		switch (handler.ShowMenu())
		{
		case MAKE:
			handler.MakeAccount();
			break;
		case DEPOSIT:
			handler.DepositMoney();
			break;
		case WITHDRAW:
			handler.WithdrawMoney();
			break;
		case INQUIRE:
			handler.ShowAllAccInfo();
			break;
		case EXIT:
			return 0;
		default:
			cout << "Illegal selection." << endl << endl;
		}
	}

	return 0;
}