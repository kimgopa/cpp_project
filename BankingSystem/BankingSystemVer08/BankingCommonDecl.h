#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int NAME_LEN = 20;

// 메뉴
enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

// 신용등급
enum { LEVEL_A = 7, LEVEL_B = 4, LEVEL_C = 2 };

// 계좌 종류
enum { NORMAL = 1, CREDIT = 2 };
