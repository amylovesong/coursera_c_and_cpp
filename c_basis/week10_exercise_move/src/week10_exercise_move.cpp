/*
 * week10_exercise_move.cpp
 *
 *  Created on: 2015年11月7日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int n = 0, m = 0, tmp = 0;
	cin >> n >> m;
	int num[n];
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	for (int i = 0; i < m; i++) {
		tmp = num[n - 1];
		for (int j = n - 1; j >= 0; j--) {
			if (j > 0) {
				num[j] = num[j - 1];
			} else {
				num[j] = tmp;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << num[i];
		if (i < n - 1) {
			cout << ' ';
		}
	}
	cout << endl;

	return 0;
}

