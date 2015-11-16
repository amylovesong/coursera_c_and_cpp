/*
 * week8_exercise_self_divide_num.cpp
 *
 *  Created on: 2015年11月6日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int n = 0;
	cin >> n;
	for (int i = 10; i <= n; i++) {
		if (i % (i / 10 + i % 10) == 0) {
			cout << i << endl;
		}
	}

	return 0;
}

