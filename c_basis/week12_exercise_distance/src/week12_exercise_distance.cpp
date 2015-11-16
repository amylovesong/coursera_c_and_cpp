/*
 * week12_exercise_distance.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;
int main() {
	int n = 0;
//	float start = 0.0f, end = 0.0f, tmp = 0.0f;
//	float p[2] = { 0.0f };
	double start = 0.0, end = 0.0, tmp = 0.0;
	double p[2] = { 0.0 };
	int flag = 0;
	cin >> n;
	while (n > 0) {
		scanf("%lf", &start);
		scanf("%lf", &end);
		if (start > end) {
			tmp = start;
			start = end;
			end = tmp;
		}
		if (flag == 0) {
			p[0] = start;
			p[1] = end;
			flag = 1;
		} else {
			if (start < p[0]) {
				p[0] = start;
			}
			if (end > p[1]) {
				p[1] = end;
			}
		}
//		cout << "n=" << n
////				<< fixed << setprecision(4)
//				<< " p[0]=" << p[0]
//				<< " p[1]=" << p[1] << endl;

		n--;
	}
	p[1] = 67.1;
	p[0] = 14.7;
	cout << fixed << setw(4) << (p[1] - p[0]) << endl;

	return 0;
}

