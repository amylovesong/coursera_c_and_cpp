/*
 * week4_exercise_big_integer.cpp
 *
 *  Created on: 2015年12月9日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <string.h>
using namespace std;

const bool debug = false;

void initArray(short * array, int length) {
	memset(array, 0, length * sizeof(short));
}

void initArray(int * array, int length) {
	memset(array, 0, length * sizeof(int));
}

void showArray(const short * array, int length) {
	if (debug) {
		cout << "test showArray length:" << length << " content:";
	}
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
	friend int * convertBigInt2Array(int * array, const BigInt & b);
	friend void convertArray2BigInt(BigInt & dest, const int * array,
			int length);
};

BigInt::BigInt(const char * n, bool flagPositive) :
		flagPositive(flagPositive) {
	length = strlen(n);
//	cout << "test constructor length:" << length << endl;
	if (length == 0) {
		num = NULL;
	} else {
		num = new short[length];
		char curDigit = '\0';
		for (int i = 0; i < length; i++) {
			curDigit = *(n + (length - 1 - i));
			num[i] = curDigit - 48; //char转为对应的int数字
		}
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
	if (debug) {
		cout << "test operator+() *this:" << *this << " b:" << b << endl;
	}
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
	if (debug) {
		cout << "test operator+ final result:" << result << endl;
	}
	return result;
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
	if (debug) {
		cout << "simplifyArray rNum:";
		showArray(rNum, rLength);
	}
	//化简最后的结果，去掉高位的0
	int index = -1;
	for (int i = rLength - 1; i >= 0; i--) {
		if (rNum[i] != 0) { //找到第一个不为0的数字位
			index = i;
			break;
		}
	}
	if (debug) {
		cout << "test simplifyArray index:" << index << endl;
	}
	if (index == -1) { //全0
		dest = BigInt("0");
	} else {
		dest.length = index + 1;
		delete[] dest.num;
		dest.num = new short[dest.length];
		memcpy(dest.num, rNum, (index + 1) * sizeof(short));
	}
}

const int D = 3;
const int BASE = 1000;
BigInt & BigInt::operator*(const BigInt & b) {
	if (debug) {
		cout << "test operator*() *this:" << *this << " b:" << b << endl;
	}
	int aLength = (length % D == 0) ? length / D : (length / D) + 1;
	int bLength = (b.length % D == 0) ? b.length / D : (b.length / D) + 1;
	if (debug) {
		cout << "test aLenght:" << aLength << " bLength:" << bLength << endl;
	}
	int *tmpA = new int[aLength], *tmpB = new int[bLength];
	initArray(tmpA, aLength);
	initArray(tmpB, bLength);
	convertBigInt2Array(tmpA, *this);
	convertBigInt2Array(tmpB, b);
	if (debug) {
		cout << "tmpA[0]:" << tmpA[0] << endl;
		cout << "tmpB[0]:" << tmpB[0] << endl;
	}
	int resultLength = aLength + bLength;
	int *tmpResult = new int[resultLength];
	int *tmp = new int[aLength];
	int indexTmp = 0;
	int *result = new int[resultLength];
	initArray(result, resultLength);
	for (int i = 0; i < bLength; i++) {
		indexTmp = 0;
		initArray(tmpResult, resultLength);
		initArray(tmp, aLength);
		if (debug) {
			cout << "test i:" << i << endl;
		}
		for (int j = 0; j < aLength; j++) {
			tmp[indexTmp] = tmpB[i] * tmpA[j];
			if (debug) {
				cout << "test tmp[" << indexTmp << "]:" << tmp[indexTmp]
						<< endl;
			}
			indexTmp++;
		}
		memcpy(tmpResult + i, tmp, indexTmp * sizeof(int));
		if (debug) {
			cout << "test tmpResult[" << indexTmp - 1 << "]:"
					<< tmpResult[indexTmp - 1] << endl;
		}
		for (int j = 0; j < indexTmp + i; j++) {
			result[j] += tmpResult[j];
		}
	}
	if (debug) {
		for (int i = 0; i < resultLength; i++) {
			cout << "test result:" << endl;
			cout << result[i] << endl;
		}
	}
	int carry = 0;
	for (int i = 0; i < resultLength; i++) {
		result[i] = result[i] + carry;
		carry = result[i] / BASE;
		result[i] = result[i] % BASE;
		if (debug) {
			cout << result[i] << endl;
		}
	}

	static BigInt finalResult;
	convertArray2BigInt(finalResult, result, resultLength);

	delete[] tmpA;
	delete[] tmpB;
	delete[] tmpResult;
	delete[] tmp;
	delete[] result;

	return finalResult;
}

int * convertBigInt2Array(int * array, const BigInt & b) {
	int index = 0;
	for (int i = 0; i < b.length; i++) {
		int tmp = b.num[i];
		for (int j = 0; j < i % D; j++) {
			tmp = tmp * 10;
		}
		array[index] = array[index] + tmp;
		if (i % D == D - 1) {
			index++;
		}
	}
	return array;
}
void convertArray2BigInt(BigInt & dest, const int * array, int length) {
	int finalResultLength = length * D;
	short * finalResultArray = new short[finalResultLength];
	initArray(finalResultArray, finalResultLength);
	int tmp = 0;
	for (int i = 0; i < length; i++) {
		tmp = array[i];
		if (debug) {
			cout << "test convertArray2BigInt tmp:" << tmp << endl;
		}
		if (tmp == 0) {
			continue;
		}
		for (int j = 0; j < D; j++) {
			finalResultArray[j + i * D] = tmp % 10;
			tmp = tmp / 10;
			if (debug) {
				cout << "test convertArray2BigInt finalResultArray:"
						<< finalResultArray[j + i * D] << endl;
			}
		}
	}
	dest.length = finalResultLength;
	dest.num = finalResultArray;
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
	if (debug) {
		cout << "test / b:" << b << endl;
	}
	static BigInt finalResult;
	if (b.length == 1 && b.num[0] == 1) { //b=1
		finalResult = *this;
		return finalResult;
	}
	if (*this == b) { //a=b
		finalResult = BigInt("1");
		return finalResult;
	}
	if (compare(*this, b)) { //a>b
		BigInt zero("0");
		finalResult.length = length;
		finalResult.num = new short[finalResult.length];
		initArray(finalResult.num, finalResult.length);

		int l = length - b.length;
		BigInt tmpB;
		tmpB.length = length;
		tmpB.num = new short[tmpB.length];
		BigInt remain = *this;
		int counter = 0;
		for (int i = l; i >= 0; i--) {
			if (remain == zero) {
				break;
			}
			initArray(tmpB.num, tmpB.length);
			tmpB.length = b.length + i;
			// 把b向左移动i位
			memcpy(tmpB.num + i, b.num, b.length * sizeof(short));
			counter = 0;
			while (true) {
				if (!compare(remain, tmpB)) {
					break;
				}
				remain = remain - tmpB;
				counter++;
			}
			if (debug) {
				cout << "test / i:" << i << " counter:" << counter << endl;
			}
			if (counter > 0) {
				finalResult.num[i] = counter;
			}
		}

		if (debug) {
			cout << "===test final result:" << finalResult << endl;
		}
		return finalResult;
	} else { // a<b
		finalResult = BigInt("0");
		return finalResult;
	}
}

ostream & operator<<(ostream & o, const BigInt & b) {
	if (debug) {
		cout << "length:" << b.length << " num:" << b.num << " content:";
	}

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
	if (debug) {
		cout << "test compare() a:" << a << " b:" << b;
	}
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
			result = !result;
		}
	} else {
		result = (a.flagPositive == true);
	}

	if (debug) {
		cout << " result:" << (result ? "a>=b" : "a<b") << endl;
	}
	return result;
}

BigInt & mMinus(const BigInt & big, const BigInt & small) {
	if (debug) {
		cout << "test big:" << big << " small:" << small << endl;
	}
	int rLength = big.length;
	short * rNum = new short[rLength];
	int i = 0, dif = 0, borrow = 0;
	for (i = 0; i < big.length; i++) {
		if (debug) {
			cout << "test big.num[" << i << "]:" << big.num[i] << endl;
		}
		if (i < small.length) {
			dif = big.num[i] - small.num[i] - borrow;
		} else {
			dif = big.num[i] - borrow;
		}
		if (dif < 0) {
			borrow = 1;		//借位
			dif += 10;
		} else {
			borrow = 0;
		}
		rNum[i] = dif;
		if (i >= small.length && borrow == 0) {	//大数比小数的位数多时，多出的高位如果没有借位的情况，则可直接copy
			break;
		}
	}
	if (i < big.length - 1) {		//多出的高位，直接copy，不需要再计算
		memcpy(rNum + (i + 1), big.num + (i + 1),
				(big.length - (i + 1)) * sizeof(short));
	}

	static BigInt result;
	simplifyArray(result, rNum, rLength);
	delete[] rNum;
	if (debug) {
		cout << "minus final result:" << result << endl;
	}
	return result;
}

int main() {
	string num1, mOperator, num2;
	cin >> num1 >> mOperator >> num2;

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

