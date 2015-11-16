/*
 * week8_exercise_sum.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int sum = 0, num_cmp = 0, n;
	cin >> num_cmp;
	for (int i = 0; i < 5; i++) {
		cin >> n;
		if (n < num_cmp) {
			sum += n;
		}
	}
	cout << sum << endl;

	return 0;
}

