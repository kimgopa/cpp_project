#pragma once
#include "BankingCommonDecl.h"

class MinusException
{
private:
	int exval;		// ������ ������ �Ǵ� �ݾ�
public:
	MinusException(int val) : exval(val)
	{}
	void ShowExceptionInfo() const
	{
		cout << "��(��)�ݾ� " << exval << "�� ��ȿ���� �ʽ��ϴ�!" << endl;
	}
};

class InsuffException
{
private:
	int balance;	// ���� �ܾ�
	int reqval;		// ��� �䱸��
public:
	InsuffException(int val, int req) : balance(val), reqval(req)
	{}
	void ShowExceptionInfo() const
	{
		cout << "�ܾ׿��� " << reqval - balance << "��(��) �����մϴ�!" << endl;
	}
};