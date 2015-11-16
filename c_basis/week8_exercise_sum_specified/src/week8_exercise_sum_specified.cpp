/*
 * week8_exercise_sum_specified.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int n = 0, k = 0;
	bool found = false;
	cin >> n >> k;
	int num[n];
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = i; j < n - 1; j++) {
			if (num[i] + num[j + 1] == k) {//第i个数依次跟后面的每一个数求和，并与k比较
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}
	if (found) {
		cout << "yes";
	} else {
		cout << "no";
	}
	return 0;
}

