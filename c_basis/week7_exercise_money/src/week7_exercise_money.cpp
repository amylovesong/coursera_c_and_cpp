/*
 * week7_exercise_money.cpp
 *
 *  Created on: 2015年11月3日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	if (n / 100 != 0) {
		cout << n / 100 << endl;
	} else {
		cout << 0 << endl;
	}
	n -= n / 100 * 100;
	if (n / 50 != 0) {
		cout << n / 50 << endl;
	} else {
		cout << 0 << endl;
	}
	n -= n / 50 * 50;
	if (n / 20 != 0) {
		cout << n / 20 << endl;
	} else {
		cout << 0 << endl;
	}
	n -= n / 20 * 20;
	if (n / 10 != 0) {
		cout << n / 10 << endl;
	} else {
		cout << 0 << endl;
	}
	n -= n / 10 * 10;
	if (n / 5 != 0) {
		cout << n / 5 << endl;
	} else {
		cout << 0 << endl;
	}
	n -= n / 5 * 5;
	cout << n << endl;
	return 0;
}

