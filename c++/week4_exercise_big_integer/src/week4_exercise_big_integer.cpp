/*
 * week4_exercise_big_integer.cpp
 *
 *  Created on: 2015年12月9日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

class BigInt {
	short *num; //index为0的元素是整数的最低位
	int length; //数字位的长度
public:
	BigInt(const char * n = "");
	~BigInt();

	BigInt & operator+(BigInt & b);
//	friend ostream & operator>>();
};

BigInt::BigInt(const char * n) {
	length = strlen(n);
//	cout << "test n:" << n << endl;
//	cout << "test length:" << length << endl;
	if (length == 0) {
		num = NULL;
	} else {
		num = new short[length];
		char curDigit = '\0';
		for (int i = 0; i < length; i++) {
			curDigit = *(n + (length - 1 - i));
			cout << "test curDigit:" << curDigit << endl;
			num[i] = curDigit - 48; //char转为对应的int数字
//				cout << "test num[i]:" << num[i] << endl;
		}
		cout << "test num:" << *num << endl;
	}
}

BigInt::~BigInt() {
	if (num) {
		delete[] num;
	}
}

BigInt & BigInt::operator+(BigInt & b) {
	int rLength = max(length, b.length) + 1;
	short *rNum = new short[rLength];
	int sum = 0, carry = 0;
	for (int i = 0; i < rLength; i++) { //从低位到高位依次相加，逢10进1
		if (i < length) {
			sum = num[i] + b.num[i] + carry;
		} else if (i < b.length) {
			sum = b.num[i] + carry;
		} else {
			sum = carry;
		}
		cout << "i:" << i << " sum:" << sum << endl;
		if (sum > 9) {
			carry = 1;
			sum -= 10;
		} else {
			carry = 0;
		}
		rNum[i] = sum;
	}
	length = rLength;
	delete[] num;
	num = rNum;

	return *this;
}

int main() {
	string num1, mOperator, num2;
	cin >> num1 >> mOperator >> num2;
	cout << "test num1:" << num1 << endl;
	cout << "test mOperator:" << mOperator << endl;
	cout << "test num2:" << num2 << endl;

	BigInt a(num1.c_str());
	BigInt b(num2.c_str());
	if (mOperator == "+") {
		a + b;
	}

	return 0;
}

