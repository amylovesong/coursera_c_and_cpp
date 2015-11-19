/*
 * week3_fibonacci.cpp
 *
 *  Created on: 2015年11月18日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

int f(int n) {
	if (n == 1) {
		return 1;
	}
	if (n == 2) {
		return 1;
	} else {
		return f(n - 1) + f(n - 2);
	}
}

int main() {
	cout << f(10) << endl;
	return 0;
}

