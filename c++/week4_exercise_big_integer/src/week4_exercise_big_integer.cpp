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

void initArray(short * array, int length) {
	for (int i = 0; i < length; i++) {
		array[i] = 0;
	}
}

void showArray(short * array, int length) {
	cout << "test showArray length:" << length << " content:";
	int i = length - 1;
	while (i >= 0) {
		cout << array[i];
		i--;
	}
	cout << endl;
}

bool isZeroArray(short * array, int length) {
	bool b = true;
	for (int i = 0; i < length; i++) {
		if (array[i] != 0) {
			b = false;
			break;
		}
	}
	return b;
}

class BigInt {
	bool flagPositive;
	short *num; //index为0的元素是整数的最低位
	int length; //数字位的长度
public:
	BigInt(const char * n = "", bool flagPositive = true);
	~BigInt();

	BigInt & operator+(BigInt & b);
	BigInt & operator-(BigInt & b);
	BigInt & operator*(BigInt & b);
	BigInt & operator/(BigInt & b);
	friend ostream & operator<<(ostream & o, const BigInt & b);
	friend bool compare(const BigInt & a, const BigInt & b);
	void minus(BigInt & tmpBig, BigInt & tmpSmall);
};

BigInt::BigInt(const char * n, bool flagPositive) :
		flagPositive(flagPositive) {
	length = strlen(n);
//	cout << "test n:" << n << endl;
//	cout << "test constructor length:" << length << endl;
	if (length == 0) {
		num = NULL;
	} else {
		num = new short[length];
		char curDigit = '\0';
		for (int i = 0; i < length; i++) {
			curDigit = *(n + (length - 1 - i));
//			cout << "test curDigit:" << curDigit << endl;
			num[i] = curDigit - 48; //char转为对应的int数字
//				cout << "test num[i]:" << num[i] << endl;
		}
//		cout << "test num:" << *num << endl;
	}
}

BigInt::~BigInt() {
	if (num) {
		delete[] num;
	}
}

BigInt & BigInt::operator+(BigInt & b) {
	short * tmpBig = NULL, *tmpSmall = NULL;
	int bigNumLength = 0, smallNumLength = 0;
	if (compare(*this, b)) {
		tmpBig = this->num;
		bigNumLength = this->length;
		tmpSmall = b.num;
		smallNumLength = b.length;
	} else {
		tmpBig = b.num;
		bigNumLength = b.length;
		tmpSmall = this->num;
		smallNumLength = this->length;
	}

	int rLength = max(length, b.length) + 1;
	short *rNum = new short[rLength];

	int sum = 0, carry = 0;
	for (int i = 0; i < rLength; i++) { //从低位到高位依次相加，逢10进1
		if (i < smallNumLength) {
			sum = tmpSmall[i] + tmpBig[i] + carry;
		} else if (i < bigNumLength) {
			sum = tmpBig[i] + carry;
		} else {
			sum = carry;
		}
//		cout << "i:" << i << " sum:" << sum << endl;
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

BigInt & BigInt::operator -(BigInt & b) {
//	cout << "test length:" << length << " b.length:" << b.length << endl;
	if (compare(*this, b)) {
		minus(*this, b);
		flagPositive = true;
		return *this;
	} else {
		minus(b, *this);
		b.flagPositive = false;
		return b;
	}
}

/**
 * return true if a >= b;
 */
BigInt & BigInt::operator*(BigInt & b) {
	BigInt result;
	result.length = max(length, b.length) * 2;
	result.num = new short[result.length];
	initArray(result.num, result.length);

	int tmpLength = b.length + 1;
	short * tmp = new short[tmpLength];
	BigInt tmpDest;
	tmpDest.length = b.length + 1 + length;
	tmpDest.num = new short[b.length + 1 + length];
	for (int i = 0; i < length; i++) {
		if (num[i] == 0) {
			continue;
		}
		//initialize array
		initArray(tmp, b.length + 1);
		initArray(tmpDest.num, tmpDest.length);

		int carry = 0, product = 0;
		for (int j = 0; j < b.length; j++) {
			product = num[i] * b.num[j] + carry;
			carry = product / 10;
			tmp[j] = product % 10;
		}
		if (carry > 0) { //最高位的进位
			tmp[b.length] = carry;
		}
//		cout << "test tmp:";
//		showArray(tmp, tmpLength);

		//向右移位，低位补0
		memcpy(tmpDest.num + i, tmp, tmpLength * sizeof(short));
//		cout << "test tmpDest.num:";
//		showArray(tmpDest.num, tmpDest.length);

		result + tmpDest;
	}
//	showArray(result.num, result.length);
	delete[] tmp;

	length = result.length;
	delete[] num;
	num = new short[length];
	memcpy(num, result.num, length * sizeof(short));

	return *this;
}

BigInt & BigInt::operator /(BigInt & b) {
	int rLength = 0;
	short * rNum = NULL;
	BigInt zero("0");
	showArray(zero.num, zero.length);

	//将除法转换成减法
	rLength = length;
	rNum = new short[rLength];
	cout << "test operator/() rNum:" << rNum << endl;
	int counter = 0;
//	cout << "test operator/() *this-b:" << *this - b << endl;
	//TODO 浅拷贝带来的内存重复回收问题
	BigInt tmp = *this - b;
	cout << "test operator/() tmp:" << tmp << endl;
	compare(tmp, zero);
//	while (compare(*this - b, zero)) {
//		counter++;
//	}

	length = rLength;
	delete[] num;
	num = rNum;

	return *this;
}

ostream & operator<<(ostream & o, const BigInt & b) {
	cout << "test operator<<() length:" << b.length << " num:" << b.num << endl;

	if (isZeroArray(b.num, b.length)) { //全0，直接输出
		cout << 0;
		return o;
	}
	if (!b.flagPositive) {
		cout << '-';
	}
	//多于一位
	int i = b.length - 1;
	bool flag = false; //从高到低输出时，遇到不为0的数时置为true，即高位的0不输出
	while (i >= 0) {
		if (b.num[i] != 0 && !flag) { //遇到不为0的数字位时，flag置为true，且只赋值一次
			flag = true;
		}
		if (!flag) { //在遇到不为0的数字位之前，不输出
			i--;
			continue;
		}
		cout << b.num[i];
		i--;
	}

	return o;
}

bool compare(const BigInt & a, const BigInt & b) {
	cout << "test compare() a:" << a << " b:" << b << endl;
	bool result = true;
	if (a.length > b.length) {
		result = true;
	} else if (a.length < b.length) {
		result = false;
	} else {
		if (a.flagPositive == b.flagPositive) { //同符号
			for (int i = a.length - 1; i >= 0; i--) {
				if (a.num[i] > b.num[i]) {
					result = true;
					break;
				} else if (a.num[i] < b.num[i]) {
					result = false;
					break;
				}
			}
			if (!a.flagPositive) {
				result = ~result;
			}
		} else {
			result = (a.flagPositive == true);
		}
	}

	cout << "test compare() result:" << (result ? "a>=b" : "a<b") << endl;
	return result;
}

void BigInt::minus(BigInt & tmpBig, BigInt & tmpSmall) {
	int rLength = 0;
	short * rNum = NULL;

//	cout << "test tmpBig:" << tmpBig << " tmpSmall:" << tmpSmall << endl;
	rLength = tmpBig.length;
	rNum = new short[rLength];
	int i = 0, n = 0;
	for (i = 0; i < tmpSmall.length; i++) {
		n = tmpBig.num[i] - tmpSmall.num[i];
		if (n < 0) {
			tmpBig.num[i + 1] -= 1; //借位
			n += 10;
		}
		rNum[i] = n;
	}
	for (i = tmpSmall.length; i < tmpBig.length; i++) {
		cout << "test tmpBig.num[i]:" << tmpBig.num[i] << endl;
		if (tmpBig.num[i] < 0) { //由于借位造成的高位为负数的情况
			tmpBig.num[i + 1] -= 1;
			tmpBig.num[i] += 10;
		}
		rNum[i] = tmpBig.num[i];
	}

	tmpBig.length = rLength;
	delete[] tmpBig.num;
	tmpBig.num = rNum;
}

int main() {
	string num1, mOperator, num2;
	cin >> num1 >> mOperator >> num2;
//	cout << "test num1:" << num1 << endl;
//	cout << "test mOperator:" << mOperator << endl;
//	cout << "test num2:" << num2 << endl;

	BigInt a(num1.c_str());
	BigInt b(num2.c_str());
	if (mOperator == "+") {
		cout << a + b << endl;
	} else if (mOperator == "-") {
		cout << a - b << endl;
	} else if (mOperator == "*") {
		cout << a * b << endl;
	} else if (mOperator == "/") {
		cout << a / b << endl;
	}

	return 0;
}

