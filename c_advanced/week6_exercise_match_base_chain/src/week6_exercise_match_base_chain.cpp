/*
 * week6_exercise_match_base_chain.cpp
 *
 *  Created on: 2015年11月26日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

void match_base_chain(const char *p) {
	while (*p != '\0') {
		switch (*p) {
		case 'A':
			cout << 'T';
			break;
		case 'T':
			cout << 'A';
			break;
		case 'G':
			cout << 'C';
			break;
		case 'C':
			cout << 'G';
			break;
		}
		p++;
	}
	cout << endl;
}

int main() {
	int n = 0;
	char base_chain[256] = { '\0' };
	cin >> n;

	while (n > 0) {
		cin >> base_chain;
		match_base_chain(base_chain);
		n--;
	}

	return 0;
}

