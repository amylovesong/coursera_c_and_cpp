/*
 * week12_exercise_year.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int a = 0;
	cin >> a;
	if (a % 4 == 0) {
		if (a % 100 == 0 && a % 400 != 0) {
			cout << "N";
		} else if (a % 3200 == 0) {
			cout << "N";
		} else {
			cout << "Y";
		}
	} else {
		cout << "N";
	}

	return 0;
}

