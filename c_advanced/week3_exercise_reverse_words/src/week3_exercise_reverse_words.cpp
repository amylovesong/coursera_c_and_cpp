/*
 * week3_exercise_reverse_words.cpp
 *
 *  Created on: 2015年11月19日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

const int length = 501;
char s[length] = { '\0' };
int index = 0;

char reverse() {
	char tmp = '\0', result = '\0';
	tmp = s[index++];
	if (tmp == ' ') {
		return tmp;
	}
	if (tmp == '\0') {//结束
		return tmp;
	} else {
		result = reverse();
		cout << tmp;
		return result;
	}
}

int main() {
	cin.getline(s, length);
	char r = '\0';
	while ((r = reverse()) != '\0') {
		cout << r;
	}
	cout << endl;

	return 0;
}

