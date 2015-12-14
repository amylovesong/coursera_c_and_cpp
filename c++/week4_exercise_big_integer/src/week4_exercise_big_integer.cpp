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

void showArray(const short * array, int length) {
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
//public:
	bool flagPositive;
	short *num; //index为0的元素是整数的最低位
	int length; //数字位的长度
public:
	BigInt(const char * n = "", bool flagPositive = true);
	BigInt(const BigInt & b);
	~BigInt();

	BigInt & operator+(const BigInt & b);
	BigInt & operator-(const BigInt & b);
	BigInt & operator*(const BigInt & b);
	BigInt & operator/(const BigInt & b);
	BigInt & operator=(const BigInt & b);
	friend bool operator==(const BigInt & a, const BigInt & b);
	friend ostream & operator<<(ostream & o, const BigInt & b);
	friend void simplifyArray(BigInt & dest, const short * rNum, int rLength);
	friend bool compare(const BigInt & a, const BigInt & b);
	friend BigInt & mMinus(const BigInt & big, const BigInt & small);
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

BigInt::BigInt(const BigInt & b) {
	*this = b;
}

BigInt::~BigInt() {
	if (num) {
		delete[] num;
	}
}

BigInt & BigInt::operator+(const BigInt & b) {
	cout << "test operator+() *this:" << *this << " b:" << b << endl;
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
	static BigInt result;
	simplifyArray(result, rNum, rLength);
//	BigInt & result = tmp;

	cout << "test operator+ final result:" << result << endl;
	return result;

//	length = rLength;
//	delete[] num;
//	num = rNum;
//
//	return *this;
}

BigInt & BigInt::operator -(const BigInt & b) {
//	cout << "test length:" << length << " b.length:" << b.length << endl;

	if (*this == b) {
		static BigInt result = BigInt("0");
		return result;
	}
	if (compare(*this, b)) {
		BigInt & result = mMinus(*this, b);
		result.flagPositive = true;
		return result;
	} else {
		BigInt & result = mMinus(b, *this);
		result.flagPositive = false;
		return result;
	}
}

void simplifyArray(BigInt & dest, const short * rNum, int rLength) {
	cout << "simplifyArray rNum:";
	showArray(rNum, rLength);
	//化简最后的结果，去掉高位的0
	int index = -1;
	for (int i = rLength - 1; i >= 0; i--) {
		if (rNum[i] != 0) { //找到第一个不为0的数字位
			index = i;
			break;
		}
	}
	cout << "test simplifyArray index:" << index << endl;
	if (index == -1) { //全0
//		tmpBig.length = 1;
//		tmpBig.flagPositive = true;
//		delete[] tmpBig.num;
//		tmpBig.num = new short[1];
//		tmpBig.num[0] = 0;
//		BigInt zero("0");
		dest = BigInt("0");
	} else {
		dest.length = index + 1;
		delete[] dest.num;
		dest.num = new short[dest.length];
		memcpy(dest.num, rNum, (index + 1) * sizeof(short));
	}
//	return dest;
}

BigInt & BigInt::operator*(const BigInt & b) {
	cout << "test operator*() *this:" << *this << " b:" << b << endl;

	BigInt result("0");
//	result.length = max(length, b.length) * 2;
//	result.num = new short[result.length];
//	initArray(result.num, result.length);

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

		result = result + tmpDest;
	}
//	showArray(result.num, result.length);
	delete[] tmp;

	cout << "test operator*() result:" << result << endl;

	static BigInt finalResult;
	simplifyArray(finalResult, result.num, result.length);

//	length = result.length;
//	delete[] num;
//	num = new short[length];
//	memcpy(num, result.num, length * sizeof(short));

	cout << "test operator*() finalResult:" << finalResult << endl;
	return finalResult;
}

bool operator==(const BigInt & a, const BigInt & b) {
	return a.flagPositive == b.flagPositive && a.length == b.length
			&& memcmp(a.num, b.num, a.length * sizeof(short)) == 0;
}

BigInt & BigInt::operator =(const BigInt & b) {
	flagPositive = b.flagPositive;
	length = b.length;
	delete[] num;
	num = new short[length];
	memcpy(num, b.num, length * sizeof(short));
	return *this;
}

BigInt & BigInt::operator /(const BigInt & b) {
	int rLength = 0;
	short * rNum = NULL;

	cout << "test / b:" << b << endl;
//	if (b.length == 1 && b.num[0] == 1) { //b=1
//		return *this;
//	}
//	if (!compare(*this, b)) { // a<b
////		BigInt zero("0");
//		*this = BigInt("0");
//		return *this;
//	}
//	if (*this == b) { //a=b
////		BigInt one("1");
//		*this = BigInt("1");
//		return *this;
//	}

	//a>b
	BigInt result("1"), step("2");
	BigInt tmp = b;
	cout << "===test / before while tmp:" << tmp << endl;
	int i = 0;
	while (true) {
		if (compare(tmp, *this)) {
			break;
		}
		result = result * step;
		cout << i << "===test / while result:" << result << endl;
		tmp = result * b;
		cout << i << "===test / while tmp:" << tmp << endl << endl;
		i++;
	}
	cout << "===test final result:" << result << endl;

	length = rLength;
	delete[] num;
	num = rNum;

	return *this;
}

ostream & operator<<(ostream & o, const BigInt & b) {
	cout << "length:" << b.length << " num:" << b.num << " content:";

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

/**
 * return true if a >= b;
 */
bool compare(const BigInt & a, const BigInt & b) {
	cout << "test compare() a:" << a << " b:" << b;
	bool result = true;

	if (a.flagPositive == b.flagPositive) { //同符号
		//先根据有效数字位判断绝对值大小
		if (a.length > b.length) {
			result = true;
		} else if (a.length < b.length) {
			result = false;
		} else {
			for (int i = a.length - 1; i >= 0; i--) {
				if (a.num[i] > b.num[i]) {
					result = true;
					break;
				} else if (a.num[i] < b.num[i]) {
					result = false;
					break;
				}
			}
		}
		//如果两数同负，则取反
		if (!a.flagPositive) {
			result = ~result;
		}
	} else {
		result = (a.flagPositive == true);
	}

	cout << " result:" << (result ? "a>=b" : "a<b") << endl;
	return result;
}

BigInt & mMinus(const BigInt & big, const BigInt & small) {
	BigInt tmpBig = big;
	BigInt tmpSmall = small;

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
		cout << "test tmpBig.num[" << i << "]:" << tmpBig.num[i] << endl;
		if (tmpBig.num[i] < 0) { //由于借位造成的高位为负数的情况
			tmpBig.num[i + 1] -= 1;
			tmpBig.num[i] += 10;
		}
		rNum[i] = tmpBig.num[i];
	}

	static BigInt result;
	simplifyArray(result, rNum, rLength);
	delete[] rNum;
	cout << "minus final result:" << result << endl;
	return result;
}

int main() {
	string num1, mOperator, num2;
	cin >> num1 >> mOperator >> num2;
//	cout << "test num1:" << num1 << endl;
//	cout << "test mOperator:" << mOperator << endl;
//	cout << "test num2:" << num2 << endl;

	BigInt a(num1.c_str());
	BigInt b(num2.c_str());

//	cout << "main a==b:" << (a == b) << endl;
//	return 0;

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

