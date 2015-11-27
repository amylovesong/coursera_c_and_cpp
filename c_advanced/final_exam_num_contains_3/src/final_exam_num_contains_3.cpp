/*
 * final_exam_num_contains_3.cpp
 *
 *  Created on: 2015年11月27日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

const int MAX_NUM_LENGTH = 6;
int index = 0;

void convertInt2Array(int num, char s[]) {
	if (num / 10 != 0) {
		convertInt2Array(num / 10, s);
	}
	s[index++] = num % 10 + 48;
	return;
}

void check(int num, int k) {
	bool flag = false;
	char s_num[MAX_NUM_LENGTH + 1] = { '\0' };
	convertInt2Array(num, s_num);
	if (num % 19 == 0) {
		int i = 0, count = 0;
		while (s_num[i] != '\0') {
			if (s_num[i] == '3') {
				count++;
			}
			i++;
		}
		if (count == k) {
			flag = true;
		}
	}

	if (flag) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}

int main() {
	int m = 0, k = 0;
	cin >> m >> k;
	check(m, k);

	return 0;
}

