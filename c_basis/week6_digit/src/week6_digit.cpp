/*
 * week6_digit.cpp
 *
 *  Created on: 2015年11月1日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;
int main() {
	int n = 0;
	cin >> n;
	int d1 = n / 100;
	n = n - (d1 * 100);
	int d2 = n / 10;
	n = n - (d2 * 10);
	int d3 = n;
	cout << d1 << endl;
	cout << d2 << endl;
	cout << d3 << endl;
	return 0;
}

