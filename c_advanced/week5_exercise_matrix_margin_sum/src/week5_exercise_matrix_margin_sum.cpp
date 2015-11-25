/*
 * week5_exercise_matrix_margin_sum.cpp
 *
 *  Created on: 2015年11月25日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

void sum_of_margin() {
	int m = 0, n = 0, result = 0;
	cin >> m >> n;
	if (m == 0 || n == 0) {
		return;
	}
	int a[m][n];
	int *p = NULL, *q = NULL;

	for (int i = 0; i < n * m; i++) {
		cin >> *(a[0] + i);
	}

	p = a[0];
	q = a[m - 1];
	for (int i = 0; i < n; i++) {
		result += *(p + i);
		//排除只有一行的情况
		if (p != q) {
			result += *(q + i);
		}
	}
	p = a[0];
	q = a[0] + (n - 1);
	for (int i = 1; i < m - 1; i++) {
		result += *(p + n*i);
		result += *(q + n*i);
	}
	cout << result << endl;
}

int main() {
	int k = 0;
	cin >> k;
	while (k > 0) {
		sum_of_margin();
		k--;
	}

	return 0;
}

