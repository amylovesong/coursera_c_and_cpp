/*
 * week12_exercise_distance.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <math.h>
using namespace std;

int main() {
	float p_x = 0.0f, p_y = 0.0f;
	double dis = 0.0, tmp = 0.0;
	int flag = 0;
	int n = 0;
	cin >> n;
	double x[n], y[n];

	for (int i = 0; i < n; i++) {
		scanf("%f", &p_x);
		scanf("%f", &p_y);
		x[i] = p_x;
		y[i] = p_y;
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			tmp = sqrt(
					(x[i] - x[j]) * (x[i] - x[j])
							+ (y[i] - y[j]) * (y[i] - y[j]));
			if (flag) {
				if (dis < tmp) {
					dis = tmp;
				}
			} else { //Initialize
				flag = 1;
				dis = tmp;
			}
		}
	}
	cout << fixed << setprecision(4) << dis << endl;

	return 0;
}

