/*
 * week10_exercise_middle.cpp
 *
 *  Created on: 2015年11月7日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int n = 0;
	while (cin >> n) {
		if (n <= 0) {
			break;
		}
		int num[n];
		for (int i = 0; i < n; i++) {
			cin >> num[i];
		}
		int max_previous = 0;
		int max = 0, min = 0, max_index = 0;
		for (int k = 0; k < n / 2 + 1; k++) {
			max = num[0], min = num[0], max_index = 0;
			for (int i = 1; i < n; i++) {
				if (max < num[i]) { //找第k个的最大值，并记录索引
					max = num[i];
					max_index = i;
				}
				if (min > num[i]) {
					min = num[i];
				}
			}
			num[max_index] = min; //把第k个最大值替换为最小值，下次循环找到的最大值就是第k+1个最大值
			if (k == n / 2 - 1) {
				max_previous = max;
			}
//			cout << 'k' << k << "max" << max << "min" << min << endl;
		}
//		cout << "max_previous" << max_previous << "max" << max << endl;
		if (n % 2 != 0) {
			cout << max << endl;
		} else {
			cout << (max_previous + max) / 2 << endl;
		}
	}

	return 0;
}

