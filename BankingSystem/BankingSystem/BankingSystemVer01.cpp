/*
* Banking System Ver 0.1.1
*/
#include <iostream>

#define NAME_LEN		20

using namespace std;

typedef struct
{
	int		accID;				// ���¹�ȣ
	int		balance;			// �ܾ�
	char	cusName[NAME_LEN];	// ���̸�
} Account;

int ShowMenu();											// �޴� ���
void MakeAccount(Account *account, int &acc_cnt);	// 1. ���°���
void DepositMoney(Account *account, int acc_cnt);	// 2. �Ա�
void WithdrawMoney(Account *account, int acc_cnt);	// 3. ���
void ShowAllAccInfo(Account *account, int acc_cnt);	// 4. �������� ��ü ���

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
	cout << "1. ���°���" << endl;
	cout << "2. �Ա�" << endl;
	cout << "3. ���" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
	cout << "���� : ";
	cin >> nSelect;
	cout << endl;

	return nSelect;
}

void MakeAccount(Account *account, int &acc_cnt)
{
	cout << "[���°���]" << endl;
	cout << "����ID : ";
	cin >> account[acc_cnt].accID;
	cout << "�̸� : ";
	cin >> account[acc_cnt].cusName;
	cout << "�Աݾ� : ";
	cin >> account[acc_cnt].balance;
	cout << endl;

	acc_cnt += 1;
}

void DepositMoney(Account *account, int acc_cnt)
{
	int accID;
	int money;

	cout << "[�Ա�]" << endl;
	cout << "����ID : ";
	cin >> accID;
	cout << "�Աݾ� : ";
	cin >> money;

	for (int i = 0; i < acc_cnt; i++)
	{
		if (account[i].accID == accID)
		{
			account[i].balance += money;
			cout << "�ԱݿϷ�" << endl << endl;
			return;
		}
	}

	cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
}

void WithdrawMoney(Account *account, int acc_cnt)
{
	int accID;
	int money;

	cout << "[���]" << endl;
	cout << "����ID : ";
	cin >> accID;
	cout << "��ݾ� : ";
	cin >> money;

	for (int i = 0; i < acc_cnt; i++)
	{
		if (account[i].accID == accID)
		{
			account[i].balance -= money;
			cout << "��ݿϷ�" << endl << endl;
			return;
		}
	}

	cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
}

void ShowAllAccInfo(Account *account, int acc_cnt)
{
	for (int i = 0; i < acc_cnt; i++)
	{
		cout << "����ID : " << account[i].accID << endl;
		cout << "�̸� : " << account[i].cusName << endl;
		cout << "�Աݾ� : " << account[i].balance << endl;
		cout << endl;
	}
}