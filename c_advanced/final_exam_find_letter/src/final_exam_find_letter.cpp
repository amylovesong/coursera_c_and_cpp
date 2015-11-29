/*
 * final_exam_find_letter.cpp
 *
 *  Created on: 2015年11月29日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

bool isLetter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void statistic(char c, char letters[], int count[]) {
	static int index_letters = 0;
	bool flag_has = false;
	int index_c = 0;
	//将小写字母转为大写字母，以便统计
	if (c > 'Z') {
		c -= 32;
	}
	for (int i = 0; i < 26; i++) {
		if (letters[i] == c) {
			flag_has = true;
			index_c = i;
			break;
		}
	}
	if (!flag_has) { //第一次遇到这个字母时，记录这个字母
		index_c = index_letters;
		letters[index_letters++] = c;
	}
	//累计出现次数
	count[index_c]++;
}

int find_k_max(int count[], int k) {
	const int times = k;
	int max = count[0];
	int index_max = 0;
	for (int t = 1; t <= times; t++) {
		for (int i = 1; i < 26; i++) {
			if (max < count[i]) {
				max = count[i];
				index_max = i;
			}
		}
		if (t < times) {
			//排除最大数不止一个的情况
			for (int i = 0; i < 26; i++) {
				if (count[i] == max) {
					count[i] = 0;
				}
			}
			max = count[0];
			index_max = 0;
		}
	}
	return index_max;
}

void find(char str[]) {
	char letters[26] = { '\0' };
	int count[26] = { 0 };

	//依次统计字母的出现情况
	int i = 0;
	while (str[i] != '\0') {
		if (isLetter(str[i])) {
			statistic(str[i], letters, count);
		}
		i++;
	}

	//寻找出现次数第二大的字母
	int index_max = find_k_max(count, 2);
	cout << letters[index_max] << '+' << char(letters[index_max] + 32) << ':'
			<< count[index_max] << endl;
}

int main() {
	char str[501];
	cin.getline(str, 501);

	find(str);

	return 0;
}

