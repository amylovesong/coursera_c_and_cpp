/*
 * week6_elephant_drink.cpp
 *
 *  Created on: 2015年11月1日
 *      Author: sunxiaoling
 */
#include <iostream>
using namespace std;
int main() {
	int h, r = 0;
	cin >> h >> r;
	double v = 3.14159 * r * r * h;
	if (20 * 1000 % (int)v == 0) {
		cout << 20 * 1000 / v;
	} else {
		cout << (int)(20 * 1000 / v) + 1;
	}
}

