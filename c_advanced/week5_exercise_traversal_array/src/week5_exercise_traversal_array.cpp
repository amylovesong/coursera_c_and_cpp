/*
 * week5_exercise_traversal_array.cpp
 *
 *  Created on: 2015年11月25日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

void traversal() {
	int row = 0, col = 0;
	cin >> row >> col;
	int a[row][col];
	int *p = NULL, *q = NULL;

	for (int i = 0; i < row * col; i++) {
		cin >> *(a[0] + i);
	}

	//先按第一行遍历
	for (int i = 0; i < col; i++) {
		p = &a[0][i];
		cout << *p << endl;

		q = p;
		for (int j = 1; j < row; j++) {
			q += (col - 1); //依次遍历下一行的前一个的元素
			if (q >= &a[j][0]) { //确保这个地址所指向的元素在当前行
				cout << *q << endl;
			}
		}
	}

	//再按最后一列遍历
	for (int i = 1; i < row; i++) {
		p = &a[i][col - 1];
		cout << *p << endl;

		q = p;
		for (int j = i + 1; j < row; j++) {
			q += (col - 1);
			if (q >= &a[j][0]) {
				cout << *q << endl;
			}
		}
	}
}

int main() {
	traversal();

	return 0;
}

