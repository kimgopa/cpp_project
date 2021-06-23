/*
	< ������� ���� ���α׷� >
	
	���
	1. ���°���
	2. �Ա�
	3. ���
	4. ��ü�� �ܾ���ȸ

	����
	- ������ ���¹�ȣ�� �ߺ����� �ƴ��Ѵ�. (�ߺ� �˻� X)
	- �Ա� �� ��ݾ��� ������ 0���� ũ��. (�Ա� �� ��ݾ� �˻� X)
	- ���� ���������� ���¹�ȣ, ���̸�, ���� �ܾ� �� ������ ���� �� �����Ѵ�.
	- �� �̻��� �� ���� ������ ���ؼ� �迭�� ����Ѵ�.
	- ���¹�ȣ�� ������ �����̴�.
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
	cout << "1. ���°���" << endl << "2. �Ա�" << endl << "3. ���" << endl << "4. �������� ��ü ���" << endl << "5. ���α׷� ����" << endl;
	cout << "���� : ";
	cin >> nSelect;
	cout << endl;

	return nSelect;
}

void MakeAccount(Account *account, int &account_cnt)
{
	cout << "[���°���]" << endl;
	cout << "����ID : ";
	cin >> account[account_cnt].ID;
	cout << "�̸� : ";
	cin >> account[account_cnt].name;
	cout << "�Աݾ� : ";
	cin >> account[account_cnt].deposit;
	cout << "\n";

	account_cnt += 1;
}

void Deposit(Account *account, int account_cnt)
{
	int ID;
	int deposit;

	cout << "[�Ա�]" << endl;
	cout << "����ID : ";
	cin >> ID;
	cout << "�Աݾ� : ";
	cin >> deposit;

	for (int i = 0; i < account_cnt; i++)
	{
		if (account[i].ID == ID)
		{
			account[i].deposit += deposit;
			break;
		}
	}

	cout << "�ԱݿϷ�\n\n";
}

void Withdraw(Account *account, int account_cnt)
{
	int ID;
	int withdraw;

	cout << "[���]" << endl;
	cout << "����ID : ";
	cin >> ID;
	cout << "��ݾ� : ";
	cin >> withdraw;

	for (int i = 0; i < account_cnt; i++)
	{
		if (account[i].ID == ID)
		{
			account[i].deposit -= withdraw;
			break;
		}
	}

	cout << "��ݿϷ�\n\n";
}

void AccountInfo(Account *account, int account_cnt)
{
	for (int i = 0; i < account_cnt; i++)
	{
		cout << "����ID : " << account[i].ID << endl;
		cout << "�̸� : " << account[i].name << endl;
		cout << "�Աݾ� : " << account[i].deposit << endl;
		cout << endl;
	}
}