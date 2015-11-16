/*
 * week10_exercise_word.cpp
 *
 *  Created on: 2015年11月7日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int max = 0, max_index = 0, counter = 0;
	char words[500] = { "" };
	cin.getline(words, 500);
	int i = 0;
	while (words[i] != '\0') {
		if (words[i] == '.') {
			if (max < counter) {
				max = counter;
				max_index = i;
			}
			break;
		}
		if (words[i] != ' ') {
			counter++;
		} else {
			if (max < counter) {
				max = counter;
				max_index = i;
			}
			counter = 0;
		}
		i++;
	}
//	cout << max << ' ' << max_index << endl;
	for (int i = max_index - max; i < max_index; i++) {
		cout << words[i];
	}
	cout << endl;

	return 0;
}

