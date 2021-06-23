/*
	< 은행계좌 관리 프로그램 >
	
	기능
	1. 계좌개설
	2. 입금
	3. 출금
	4. 전체고객 잔액조회

	가정
	- 통장의 계좌번호는 중복되지 아니한다. (중복 검사 X)
	- 입금 및 출금액은 무조건 0보다 크다. (입금 및 출금액 검사 X)
	- 고객의 계좌정보는 계좌번호, 고객이름, 고객의 잔액 세 가지만 저장 및 관리한다.
	- 둘 이상의 고객 정보 저장을 위해서 배열을 사용한다.
	- 계좌번호는 정수의 형태이다.
*/

#include <iostream>

using namespace std;

typedef struct Account
{
	int ID;
	char name[10];
	int deposit;
} Account;

int ShowMenu();
void MakeAccount(Account *account, int &account_cnt);
void Deposit(Account *account, int account_cnt);
void Withdraw(Account *account, int account_cnt);
void AccountInfo(Account *account, int account_cnt);

int main(void)
{
	Account account[100];
	int account_cnt = 0;

	while (1)
	{
		switch (ShowMenu())
		{
		case 1:
			MakeAccount(account, account_cnt);
			break;
		case 2:
			Deposit(account, account_cnt);
			break;
		case 3:
			Withdraw(account, account_cnt);
			break;
		case 4:
			AccountInfo(account, account_cnt);
			break;
		case 5:
			return 0;
		}
	}

	return 0;
}

int ShowMenu()
{
	int nSelect;
	cout << "------ Menu -----" << endl;
	cout << "1. 계좌개설" << endl << "2. 입금" << endl << "3. 출금" << endl << "4. 계좌정보 전체 출력" << endl << "5. 프로그램 종료" << endl;
	cout << "선택 : ";
	cin >> nSelect;
	cout << endl;

	return nSelect;
}

void MakeAccount(Account *account, int &account_cnt)
{
	cout << "[계좌개설]" << endl;
	cout << "계좌ID : ";
	cin >> account[account_cnt].ID;
	cout << "이름 : ";
	cin >> account[account_cnt].name;
	cout << "입금액 : ";
	cin >> account[account_cnt].deposit;
	cout << "\n";

	account_cnt += 1;
}

void Deposit(Account *account, int account_cnt)
{
	int ID;
	int deposit;

	cout << "[입금]" << endl;
	cout << "계좌ID : ";
	cin >> ID;
	cout << "입금액 : ";
	cin >> deposit;

	for (int i = 0; i < account_cnt; i++)
	{
		if (account[i].ID == ID)
		{
			account[i].deposit += deposit;
			break;
		}
	}

	cout << "입금완료\n\n";
}

void Withdraw(Account *account, int account_cnt)
{
	int ID;
	int withdraw;

	cout << "[출금]" << endl;
	cout << "계좌ID : ";
	cin >> ID;
	cout << "출금액 : ";
	cin >> withdraw;

	for (int i = 0; i < account_cnt; i++)
	{
		if (account[i].ID == ID)
		{
			account[i].deposit -= withdraw;
			break;
		}
	}

	cout << "출금완료\n\n";
}

void AccountInfo(Account *account, int account_cnt)
{
	for (int i = 0; i < account_cnt; i++)
	{
		cout << "계좌ID : " << account[i].ID << endl;
		cout << "이름 : " << account[i].name << endl;
		cout << "입금액 : " << account[i].deposit << endl;
		cout << endl;
	}
}