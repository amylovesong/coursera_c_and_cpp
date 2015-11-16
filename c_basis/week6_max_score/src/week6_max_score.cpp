/*
 * week6_max_score.cpp
 *
 *  Created on: 2015年11月1日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;
int main() {
	int n, score, max = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> score;
		if (max < score) {
			max = score;
		}
	}
	cout << max;
	return 0;
}

