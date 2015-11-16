/*
 * week2_exercise_cold.cpp
 *
 *  Created on: 2015年11月14日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

int main() {
	int n = 0, m = 0, result = 0;
	cin >> n;
	char a[n][n], copy[n][n];
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			cin >> a[row][col];
			copy[row][col] = a[row][col];
		}
	}
	cin >> m;
	for (int i = 0; i < m - 1; i++) {
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				if (a[row][col] == '@') {
					//top
					if (row > 0 && a[row - 1][col] == '.') {
						copy[row - 1][col] = '@';
					}
					//bottom
					if (row < n - 1 && a[row + 1][col] == '.') {
						copy[row + 1][col] = '@';
					}
					//left
					if (col > 0 && a[row][col - 1] == '.') {
						copy[row][col - 1] = '@';
					}
					//right
					if (col < n - 1 && a[row][col + 1] == '.') {
						copy[row][col + 1] = '@';
					}
				}
			}
		}
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				a[row][col] = copy[row][col];
			}
		}
//		cout << "m=" << i << endl;
//		for (int row = 0; row < n; row++) {
//			for (int col = 0; col < n; col++) {
//				cout << (char) (a[row][col]);
//			}
//			cout << endl;
//		}
	}
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (a[row][col] == '@') {
				result++;
			}
		}
	}
	cout << result << endl;

	return 0;
}

