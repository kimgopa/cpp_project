#pragma once
#include "BankingCommonDecl.h"

class Exception
{
public:
	virtual void ShowExceptionReason() = 0;	// ���� �����Լ�
};

class MinusException : public Exception
{
public:
	void ShowExceptionReason()
	{
		cout << "[���� �޽��� : 0 ���� ū ���� �Է��ϼ���]" << endl << endl;;
	}
};

class WithdrawException : public Exception
{
private:
	int req;
public:
	WithdrawException(int money) : req(money)
	{ }
	void ShowExceptionReason()
	{
		cout << "[���� �޽��� : �ܰ� ����. " << req << "���� ��ݺҰ�]" << endl << endl;
	}
};

class DepositException : public Exception
{
private:
	int req;
public:
	DepositException(int money) : req(money)
	{ }
	void ShowExceptionReason()
	{
		cout << "[���� �޽��� : " << req << "���� �ԱݺҰ�]" << endl;
	}
};