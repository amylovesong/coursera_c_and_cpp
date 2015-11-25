/*
 * week5_exercise_words_composing.cpp
 *
 *  Created on: 2015年11月25日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <string.h>
using namespace std;

void compose_words() {
	const int length = 41;
	const int maxWidth = 80;
	int n = 0;
	cin >> n;
	char str[n][length];
	for (int i = 0; i < n; i++) {
		cin >> str[i];
	}

	char (*p)[length] = str;
	int tmp = 0;
	bool flag_line_start = false;//是否为文本行首
	while (p <= &str[n - 1]) {
		flag_line_start = (tmp == 0);
		tmp += strlen(*p);
		if (tmp < maxWidth) {
			if (!flag_line_start) {
				cout << ' ';
				tmp += 1; //算上空格的长度
			}
			cout << *p;
			p++;
		} else {
			cout << endl;
			tmp = 0;
		}
	}
}

int main() {
	compose_words();

	return 0;
}

