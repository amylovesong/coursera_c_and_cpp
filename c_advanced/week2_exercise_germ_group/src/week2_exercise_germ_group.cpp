/*
 * week2_exercise_germ_group.cpp
 *
 *  Created on: 2015年11月14日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

//5
//1 10 3456
//2 10 5644
//3 10 4566
//4 20 234
//5 20 232

int main() {
	int n = 0;
	cin >> n;
	int id[n];
	double rate[n];
	for (int i = 0; i < n; i++) {
		int before = 0, after = 0;
		cin >> id[i] >> before >> after;
		rate[i] = (double) after / before;
	}

	//sort
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (rate[j] < rate[j + 1]) {
				double tmp_rate = rate[j];
				rate[j] = rate[j + 1];
				rate[j + 1] = tmp_rate;
				int tmp_id = id[j];
				id[j] = id[j + 1];
				id[j + 1] = tmp_id;
			}
		}
	}

	double maxDiff = 0;
	int maxDiffIndex = 0;
	for (int i = 0; i < n - 1; i++) {
		double diff = rate[i] - rate[i + 1];
		if (maxDiff < diff) {
			maxDiff = diff;
			maxDiffIndex = i;
		}
	}

	cout << maxDiffIndex + 1 << endl;
	for (int i = maxDiffIndex; i >= 0; i--) {
		cout << id[i] << endl;
	}
	cout << n - (maxDiffIndex + 1) << endl;
	for (int i = n - 1; i > maxDiffIndex; i--) {
		cout << id[i] << endl;
	}

	return 0;
}

