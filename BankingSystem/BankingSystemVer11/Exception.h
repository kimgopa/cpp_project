#pragma once
#include "BankingCommonDecl.h"

class Exception
{
public:
	virtual void ShowExceptionReason() = 0;	// 순수 가상함수
};

class MinusException : public Exception
{
public:
	void ShowExceptionReason()
	{
		cout << "[예외 메시지 : 0 보다 큰 값을 입력하세요]" << endl << endl;;
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
		cout << "[예외 메시지 : 잔고 부족. " << req << "원은 출금불가]" << endl << endl;
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
		cout << "[예외 메시지 : " << req << "원은 입금불가]" << endl;
	}
};