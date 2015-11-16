/*
 * week2_exercise_the_four_lakes.cpp
 *
 *  Created on: 2015年11月16日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

int main() {
	int py = 0, dt = 0, t = 0, hz = 0;
	bool a = false, b = false, c = false, d = false;

	for (py = 1; py <= 4; py++) {
		for (dt = 1; dt <= 4; dt++) {
			for (t = 1; t <= 4; t++) {
				for (hz = 1; hz <= 4; hz++) {
					// 排除排名相等的情况
					if ((py - dt) * (py - t) * (py - hz) * (dt - t) * (dt - hz)
							* (t - hz) != 0) {
						a = (dt == 1) + (hz == 4) + (py == 3) == 1;
						b = (hz == 1) + (dt == 4) + (py == 2) + (t == 3) == 1;
						c = (hz == 4) + (dt == 3) == 1;
						d = (py == 1) + (t == 4) + (hz == 2) + (dt == 3) == 1;
						if (a && b && c && d) {
							cout << py << endl;
							cout << dt << endl;
							cout << t << endl;
							cout << hz << endl;
						}
					}
				}
			}
		}
	}

	return 0;
}

