/*
 * week7_exercise_string_operation.cpp
 *
 *  Created on: 2015年12月24日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

const bool debug = true;

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

bool stringOperation(string strs[], int length, string oper);

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
		if (stringOperation(strs, n, oper)) {
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

bool contains(string origin, string substr) {
	return origin.find(substr) != string::npos;
}

bool stringOperation(string strs[], int length, string oper) {
	string N = "", X = "", L = "", S1 = "", S2 = "", S = "";
	if (debug) {
		cout << "oper: " << oper << endl;
	}
	if (oper == OPERATION_COPY) {

	} else if (oper == OPERATION_ADD) {

	} else if (oper == OPERATION_FIND) {

	} else if (oper == OPERATION_RFIND) {

	} else if (isStartWith(oper, OPERATION_INSERT)) { //insert copy 1 find 2 1 2 2 2
		S = oper.substr(oper.find(' '));
		if (debug) {
			cout << "insert S:" << S << endl;
		}
		if (isOperator(S)) {
			stringOperation(strs, length, S);
		} else {

			cin >> N;
			if (isOperator(N)) {
				stringOperation(strs, length, N);
			} else {
				cin >> X;
				if (isOperator(X)) {
					stringOperation(strs, length, X);
				} else {
					int n = atoi(N.c_str());
					int x = atoi(X.c_str());
					strs[n - 1].insert(x, S);
				}
			}
		}
	} else if (oper == OPERATION_RESET) {

	} else if (oper == OPERATION_PRINTALL) {
		for (int i = 0; i < length; i++) {
			cout << strs[i] << endl;
		}
	} else if (isStartWith(oper, OPERATION_PRINT)) {
		oper = oper.substr(oper.find(' '));
		int num = atoi(oper.c_str());
		if (debug) {
			cout << "test print num:" << num << endl;
		}
		cout << strs[num - 1] << endl;
	} else if (oper == OPERATION_OVER) {
		return true;
	}
	return false;
}

