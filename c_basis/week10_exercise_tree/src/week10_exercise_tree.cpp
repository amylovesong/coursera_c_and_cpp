/*
 * week10_exercise_tree.cpp
 *
 *  Created on: 2015年11月7日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int L = 0, M = 0, start = 0, end = 0;
	cin >> L >> M;
	int tree[L + 1];
	for (int i = 0; i <= L; i++) {
		tree[i] = 1;
	}
	for (int i = 0; i < M; i++) {
		cin >> start >> end;
		for (int j = start; j <= end; j++) {
			if (tree[j] == 1) {
				tree[j] = 0;
			}
		}
	}
	int counter = 0;
	for (int i = 0; i <= L; i++) {
		if (tree[i] == 1) {
			counter++;
		}
	}
	cout << counter << endl;

	return 0;
}

