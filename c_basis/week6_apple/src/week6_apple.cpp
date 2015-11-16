/*
 * week6_apple.cpp
 *
 *  Created on: 2015年11月1日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;
int main() {
	int n, x, y = 0;
	cin >> n >> x >> y;
	int result = 0;
	if (y % x == 0) {
		result = n - y / x;
	} else {
		result = n - (y / x + 1);
	}
	if (result < 0) {
		cout << 0;
	} else {
		cout << result;
	}
	return 0;
}

