/*
 * week3_exercise_match_parenthesis.cpp
 *
 *  Created on: 2015��11��19��
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

const int length = 101;
char s[length] = { '\0' };
bool flag[length] = { false };
int index = -1;

void match() {
	index++;
	char c = s[index];
	if (c == '\0') { //��β
		return;
	}
	if (c == ')') { //����������
		//��ǰѰ������ƥ���������
		for (int i = index - 1; i >= 0; i--) {
			//�ҵ�ƥ���ʱ�����¶�Ӧλ�õ�flag
			if (s[i] == '(' && !flag[i]) {
				flag[index] = true;
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
			} else {		//�����ַ�
				cout << ' ';
			}
		} else {
			cout << ' ';
		}
	}
	cout << endl;
}

int main() {
	cin.getline(s, length);
	while (s[0] != '\0') {
		match();
		show_result();

		cin.getline(s, length);
	}

	return 0;
}

