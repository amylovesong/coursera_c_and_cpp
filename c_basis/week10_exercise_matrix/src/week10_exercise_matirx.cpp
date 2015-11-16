/*
 * week10_exercise_matirx.cpp
 *
 *  Created on: 2015年11月7日
 *      Author: sunxiaoling
 */

#include<iostream>
#include<iomanip>
using namespace std;
int main() {
	int num[5][5] = { 0 };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> num[i][j];
		}
	}
	int n = 0, m = 0;
	cin >> n >> m;
	if ((n >= 0 && n < 5) && (m >= 0 && m < 5)) {
		int tmp = 0;
		for (int i = 0; i < 5; i++) {
			tmp = num[n][i];
			num[n][i] = num[m][i];
			num[m][i] = tmp;
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				cout << setw(4) << num[i][j];
			}
			cout << endl;
		}
	} else {
		cout << "error" << endl;
	}

	return 0;
}

