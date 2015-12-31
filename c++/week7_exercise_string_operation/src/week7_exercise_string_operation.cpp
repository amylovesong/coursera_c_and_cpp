/*
 * week7_exercise_string_operation.cpp
 *
 *  Created on: 2015年12月24日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

const bool debug = false;

const int MAX_STR_LENGTH = 501;
const int LINE_LENGTH = 101;

const string OPERATION_COPY = "copy";
const string OPERATION_ADD = "add";
const string OPERATION_FIND = "find";
const string OPERATION_RFIND = "rfind";
const string OPERATION_INSERT = "insert";
const string OPERATION_RESET = "reset";
const string OPERATION_PRINT = "print";
const string OPERATION_PRINTALL = "printall";
const string OPERATION_OVER = "over";

string stringOperation(string strs[], int length, string oper);

int main() {
	int n;
	cin >> n;
	string strs[n];
	char * tmp = new char[MAX_STR_LENGTH];
	cin.getline(tmp, MAX_STR_LENGTH);
	for (int i = 0; i < n; i++) {
		cin.getline(tmp, MAX_STR_LENGTH);
		strs[i] = tmp;
		if (debug) {
			cout << "i:" << i << " tmp:" << tmp << " strs[i]" << strs[i]
					<< endl;
		}
	}
	string oper;
	char * buf = new char[LINE_LENGTH];
	while (true) {
		cin.getline(buf, LINE_LENGTH);
		oper = buf;
		if (stringOperation(strs, n, oper) == OPERATION_OVER) {
			break;
		}
	}

	return 0;
}

bool isStartWith(string origin, string substr) {
	return origin.find(substr) == 0;
}

bool isOperator(string s) {
	return isStartWith(s, OPERATION_ADD) || isStartWith(s, OPERATION_COPY)
			|| isStartWith(s, OPERATION_FIND)
			|| isStartWith(s, OPERATION_INSERT)
			|| isStartWith(s, OPERATION_RESET)
			|| isStartWith(s, OPERATION_RFIND);
}

string getNextWord(string oper) {
	return oper.substr(0, oper.find(' '));
}

string getNextOper(string oper) {
	return oper.substr(oper.find(' ') + 1);
}

string stringOperation(string strs[], int length, string oper) {
	//其中N，X，L可由find与rfind操作表达式构成，S，S1，S2可由copy与add操作表达式构成。
	string N = "", X = "", L = "", S1 = "", S2 = "", S = "";
	if (debug) {
		cout << "stringOperation oper:" << oper << endl;
	}
	if (isStartWith(oper, OPERATION_COPY)) { //copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		N = getNextWord(oper);
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		X = getNextWord(oper);
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		L = getNextWord(oper);
		int n = atoi(N.c_str());
		int x = atoi(X.c_str());
		int l = atoi(L.c_str());
		string result = strs[n - 1].substr(x, l);
		oper.replace(0, L.length(), result);
		if (debug) {
			cout << "test after copy, oper is:" << oper << endl;
		}
		return oper;
	} else if (isStartWith(oper, OPERATION_ADD)) { //add S1 S2：判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，若不是，则作字符串加法，返回的值为一字符串。
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		S1 = getNextWord(oper);
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		S2 = getNextWord(oper);
		string result = "";
		if (S1.length() > strlen("99999")
				|| S1.find_first_not_of("1234567890") != string::npos
				|| S1.length() > strlen("99999")
				|| S2.find_first_not_of("1234567890") != string::npos) {
			result = S1 + S2;
		} else {
			int s1 = atoi(S1.c_str());
			int s2 = atoi(S2.c_str());
			stringstream ss;
			ss << (s1+s2);
			ss >> result;
		}
		oper.replace(0, S2.length(), result);
		if(debug){
			cout << "test after add, result is:" << result << endl;
			cout << "test after add, oper is:" << oper << endl;
		}
		return oper;
	} else if (isStartWith(oper, OPERATION_FIND) //find S N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
			|| isStartWith(oper, OPERATION_RFIND)) { //rfind S N：在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
		bool isfind = isStartWith(oper, OPERATION_FIND);
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		S = getNextWord(oper);
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		N = getNextWord(oper);
		int n = atoi(N.c_str());
		unsigned int pos = string::npos;
		if (isfind) {
			pos = strs[n - 1].find(S);
		} else {
			pos = strs[n - 1].rfind(S);
		}
		if (debug) {
			cout << "test find/rfind pos:" << pos << endl;
		}
		if (pos == string::npos) {
			pos = S.length();
		}
		string result = "";
		stringstream ss;
		ss << pos;
		ss >> result;
		oper.replace(0, N.length(), result);
		if (debug) {
			cout << "test find/rfind result:" << pos << endl;
			cout << "test after find/rfind, oper is:" << oper << endl;
		}
		return oper;
	} else if (isStartWith(oper, OPERATION_INSERT)) { //insert S N X：在第N个字符串的第X个字符位置中插入S字符串。
		oper = getNextOper(oper);
		if (debug) {
			cout << "insert oper:" << oper << endl;
		}
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		S = getNextWord(oper);
		if (debug) {
			cout << "insert S:" << S << endl;
		}
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		N = getNextWord(oper);
		if (debug) {
			cout << "insert N:" << N << endl;
		}
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		X = getNextWord(oper);
		if (debug) {
			cout << "insert X:" << X << endl;
		}
		int n = atoi(N.c_str());
		int x = atoi(X.c_str());
		strs[n - 1].insert(x, S);
	} else if (isStartWith(oper, OPERATION_RESET)) { //reset S N：将第N个字符串变为S。
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		S = getNextWord(oper);
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		N = getNextWord(oper);
		int n = atoi(N.c_str());
		strs[n - 1] = S;
	} else if (isStartWith(oper, OPERATION_PRINTALL)) { //printall：打印输出所有字符串。
		for (int i = 0; i < length; i++) {
			cout << strs[i] << endl;
		}
	} else if (isStartWith(oper, OPERATION_PRINT)) { //print N：打印输出第N个字符串。
		oper = getNextOper(oper);
		if (isOperator(oper)) {
			oper = stringOperation(strs, length, oper);
		}
		N = getNextWord(oper);
		int n = atoi(N.c_str());
		if (debug) {
			cout << "test print n:" << n << endl;
		}
		cout << strs[n - 1] << endl;
	} else if (isStartWith(oper, OPERATION_OVER)) { //over：结束操作。
		return OPERATION_OVER;
	}
	return "";
}

