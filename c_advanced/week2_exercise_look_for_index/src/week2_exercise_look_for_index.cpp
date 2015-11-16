/*
 * week2_exercise_look_for_index.cpp
 *
 *  Created on: 2015年11月12日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;
int main() {
	int n = 0, result = 0, flag = 0;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		if (a[i] == i) {
			result = i;
			flag = 1;
			break;
		}
	}
	if (flag) {
		cout << result << endl;
	} else {
		cout << 'N' << endl;
	}

	return 0;
}

