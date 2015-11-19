/*
 * week3_exercise_jiaogucaixiang.cpp
 *
 *  Created on: 2015年11月19日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

int tmp = 0;

void fun(int num) {
	if (num > 1) {
		if (num % 2 == 0) { //偶数
			tmp = num / 2;
			cout << num << "/2=" << tmp << endl;
		} else {
			tmp = num * 3 + 1;
			cout << num << "*3+1=" << tmp << endl;
		}
		fun(tmp);
	}
}

int main() {
	int num = 0;
	cin >> num;
	fun(num);
	cout << "End";

	return 0;
}

