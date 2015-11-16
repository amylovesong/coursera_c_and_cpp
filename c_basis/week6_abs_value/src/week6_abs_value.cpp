/*
 * week6_abs_value.cpp
 *
 *  Created on: 2015年11月1日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;
int main() {
	int num = 0;
	int maxOdd = 0;
	int minEven = 0;
	for (int i = 0; i < 6; i++) {
		cin >> num;
		if (num % 2 == 0) {
			if (minEven == 0) {
				minEven = num;
			} else if (minEven > num) {
				minEven = num;
			}
		} else {
			if (maxOdd == 0) {
				maxOdd = num;
			} else if (maxOdd < num) {
				maxOdd = num;
			}
		}
	}
	if ((maxOdd - minEven) > 0) {
		cout << (maxOdd - minEven);
	} else {
		cout << (minEven - maxOdd);
	}
	return 0;
}

