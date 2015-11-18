/*
 * week3_reverse_polish.cpp
 *
 *  Created on: 2015年11月18日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <math.h>
using namespace std;

double notation() {
	char str[10];
	cin >> str;
	cout << str << endl;
	switch (str[0]) {
	case '+':
		return notation() + notation();
	case '-':
		return notation() - notation();
	case '*':
		return notation() * notation();
	case '/':
		return notation() / notation();
	default:
		return atof(str);
	}
}

int main() {
	cout << notation();
	return 0;
}

