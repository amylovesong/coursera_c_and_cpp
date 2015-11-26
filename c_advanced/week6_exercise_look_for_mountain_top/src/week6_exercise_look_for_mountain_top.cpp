/*
 * week6_exercise_look_for_mountain_top.cpp
 *
 *  Created on: 2015年11月26日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

const int INITIAL_VALUE = -1;

void look_for_mountain_top(const int (*p)[20]) {
	int cur = 0;
	int flag = 0;
	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 20; col++) {
			flag = 0;
			cur = *(*(p + row) + col);
			if (cur == -1) {
				continue;
			}
			//up
			if (row > 0) {
				if (cur >= *(*(p + row - 1) + col)) {
					flag++;
				} else {
					flag--;
				}
			} else {
				flag++;
			}
			// below
			if (row < 20 - 1 && *(*(p + row + 1) + col) != INITIAL_VALUE) {
				if (cur >= *(*(p + row + 1) + col)) {
					flag++;
				} else {
					flag--;
				}
			} else {
				flag++;
			}
			//left
			if (col > 0) {
				if (cur >= *(*(p + row) + col - 1)) {
					flag++;
				} else {
					flag--;
				}
			} else {
				flag++;
			}
			//right
			if (col < 20 - 1 && *(*(p + row) + col + 1) != INITIAL_VALUE) {
				if (cur >= *(*(p + row) + col + 1)) {
					flag++;
				} else {
					flag--;
				}
			} else {
				flag++;
			}
			if (flag == 4) {
				cout << row << ' ' << col << endl;
			}
		}
	}
}

int main() {
	int m = 0, n = 0;
	int area[20][20];
	//Initialize array
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			area[i][j] = INITIAL_VALUE;
		}
	}
	cin >> m >> n;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> area[i][j];
		}
	}
	look_for_mountain_top(area);

	return 0;
}

