/*
* Banking System Ver 0.1.1
*/
#include <iostream>

#define NAME_LEN		20

using namespace std;

typedef struct
{
	int		accID;				// 계좌번호
	int		balance;			// 잔액
	char	cusName[NAME_LEN];	// 고객이름
} Account;

int ShowMenu();											// 메뉴 출력
void MakeAccount(Account *account, int &acc_cnt);	// 1. 계좌개설
void DepositMoney(Account *account, int acc_cnt);	// 2. 입금
void WithdrawMoney(Account *account, int acc_cnt);	// 3. 출금
void ShowAllAccInfo(Account *account, int acc_cnt);	// 4. 계좌정보 전체 출력

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

Account accArr[100];
int acc_cnt = 0;

int main(void)
{
	while (1)
	{
		switch (ShowMenu())
		{
		case MAKE:
			MakeAccount(accArr, acc_cnt);
			break;
		case DEPOSIT:
			DepositMoney(accArr, acc_cnt);
			break;
		case WITHDRAW:
			WithdrawMoney(accArr, acc_cnt);
			break;
		case INQUIRE:
			ShowAllAccInfo(accArr, acc_cnt);
			break;
		case EXIT:
			return 0;
		default:
			cout << "Illegal selection." << endl << endl;
		}
	}

	return 0;
}

int ShowMenu()
{
	int nSelect;
	cout << "------ Menu -----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입금" << endl;
	cout << "3. 출금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
	cout << "선택 : ";
	cin >> nSelect;
	cout << endl;

	return nSelect;
}

void MakeAccount(Account *account, int &acc_cnt)
{
	cout << "[계좌개설]" << endl;
	cout << "계좌ID : ";
	cin >> account[acc_cnt].accID;
	cout << "이름 : ";
	cin >> account[acc_cnt].cusName;
	cout << "입금액 : ";
	cin >> account[acc_cnt].balance;
	cout << endl;

	acc_cnt += 1;
}

void DepositMoney(Account *account, int acc_cnt)
{
	int accID;
	int money;

	cout << "[입금]" << endl;
	cout << "계좌ID : ";
	cin >> accID;
	cout << "입금액 : ";
	cin >> money;

	for (int i = 0; i < acc_cnt; i++)
	{
		if (account[i].accID == accID)
		{
			account[i].balance += money;
			cout << "입금완료" << endl << endl;
			return;
		}
	}

	cout << "유효하지 않은 ID입니다." << endl << endl;
}

void WithdrawMoney(Account *account, int acc_cnt)
{
	int accID;
	int money;

	cout << "[출금]" << endl;
	cout << "계좌ID : ";
	cin >> accID;
	cout << "출금액 : ";
	cin >> money;

	for (int i = 0; i < acc_cnt; i++)
	{
		if (account[i].accID == accID)
		{
			account[i].balance -= money;
			cout << "출금완료" << endl << endl;
			return;
		}
	}

	cout << "유효하지 않은 ID입니다." << endl << endl;
}

void ShowAllAccInfo(Account *account, int acc_cnt)
{
	for (int i = 0; i < acc_cnt; i++)
	{
		cout << "계좌ID : " << account[i].accID << endl;
		cout << "이름 : " << account[i].cusName << endl;
		cout << "입금액 : " << account[i].balance << endl;
		cout << endl;
	}
}