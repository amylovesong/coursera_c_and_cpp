/*
 * week10_exercise_cell.cpp
 *
 *  Created on: 2015年11月7日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int n = 0, result = 0;
	cin >> n;
	int cell[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> cell[i][j];
		}
	}
	for (int i = 1; i < n - 1; i++) {
		for (int j = 1; j < n - 1; j++) {
			if (cell[i][j] + 50 <= cell[i - 1][j]
					&& cell[i][j] + 50 <= cell[i + 1][j]
					&& cell[i][j] + 50 <= cell[i][j - 1]
					&& cell[i][j] + 50 <= cell[i][j + 1]) {
				result++;
			}
		}
	}
	cout << result << endl;

	return 0;
}

