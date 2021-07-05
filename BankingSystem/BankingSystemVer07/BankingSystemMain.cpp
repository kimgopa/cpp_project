/*
* Banking System Ver 0.7.0
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "BankingCommonDecl.h"
#include "AccountHandler.h"

using namespace std;

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