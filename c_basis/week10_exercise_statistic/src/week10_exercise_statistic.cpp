/*
 * week10_exercise_statise.cpp
 *
 *  Created on: 2015年11月7日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	const int counts = 80;
	char s[counts] = { "" };
	cin.getline(s, counts);
	int result[5] = { 0 };
	for (int i = 0; i < counts; i++) {
		switch (s[i]) {
		case 'a':
			result[0]++;
			break;
		case 'e':
			result[1]++;
			break;
		case 'i':
			result[2]++;
			break;
		case 'o':
			result[3]++;
			break;
		case 'u':
			result[4]++;
			break;
		}
	}
	for (int i = 0; i < 5; i++) {
		cout << result[i];
		if (i < 5) {
			cout << ' ';
		}
	}

	return 0;
}

