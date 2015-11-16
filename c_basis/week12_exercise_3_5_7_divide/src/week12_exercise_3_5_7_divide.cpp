/*
 * week12_exercise_3_5_7_divide.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int num = 0, flag = 0;
	while (cin >> num) {
		flag = 0;
		if (num % 3 == 0) {
			cout << 3;
			flag = 1;
		}
		if (num % 5 == 0) {
			if (flag == 1) {
				cout << " ";
			}
			cout << 5;
			flag = 1;
		}
		if (num % 7 == 0) {
			if (flag == 1) {
				cout << " ";
			}
			cout << 7;
			flag = 1;
		}
		if (flag != 1) {
			cout << 'n';
		}
		cout << endl;
	}

	return 0;
}

