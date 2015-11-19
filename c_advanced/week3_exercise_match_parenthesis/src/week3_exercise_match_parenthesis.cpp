/*
 * week3_exercise_match_parenthesis.cpp
 *
 *  Created on: 2015年11月19日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

const int length = 101;
char s[length] = { '\0' };
bool flag[length] = { false };
int p = -1;

void match() {
	p++;
	char c = s[p];
	if (c == '\0') { //结尾
		return;
	}
	if (c == ')') { //遇到右括号
		//向前寻找与它匹配的左括号
		for (int i = p - 1; i >= 0; i--) {
			//找到匹配的时，更新对应位置的flag
			if (s[i] == '(' && !flag[i]) {
				flag[p] = true;
				flag[i] = true;
				break;
			}
		}
	}
	match();
}

void show_result() {
	cout << s << endl;
	for (int i = 0; i < length; i++) {
		if (s[i] == '\0') {
			break;
		}
		if (!flag[i]) {
			if (s[i] == '(') {
				cout << '$';
			} else if (s[i] == ')') {
				cout << '?';
			} else {		//其他字符
				cout << ' ';
			}
		} else {
			cout << ' ';
		}
	}
	cout << endl;
}

void reset() {
	for (int i = 0; i < length; i++) {
		s[i] = '\0';
		flag[i] = false;
	}
	p = -1;
}

int main() {
	cin.getline(s, length);
	while (s[0] != '\0') {
		match();
		show_result();

		reset();
		cin.getline(s, length);
	}

	return 0;
}
