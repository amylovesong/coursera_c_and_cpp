/*
 * week3_apples.cpp
 *
 *  Created on: 2015年11月17日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

int count(int m, int n) {
	if (m <= 1 || n <= 1) {//不能剩下苹果，所以这里的盘子数应至少有一个
		return 1;
	}
	if (m < n) {
		return count(m, m);
	} else {
		return count(m, n - 1) + count(m - n, n);
	}
}

int main() {
	int apples, plates;
	cin >> apples >> plates;
	cout << count(apples, plates);

	return 0;
}

