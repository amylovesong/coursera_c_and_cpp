/*
 * week3_exercise_queue.cpp
 *
 *  Created on: 2015��11��19��
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

const int length = 101;
char children[length] = { '\0' };
bool flag[length] = { false };
char boy = '\0', girl = '\0';
int index = -1;
int p_girl = -1;

void queue() {
	index++;
	char child = children[index];
//	cout << "index=" << index << ' ' << "child=" << child << endl;
	if (child == '\0') {
		return;
	}
	if (boy == '\0') {
		boy = child;
	}
	if (child != boy) { //����һ��СŮ��
		girl = child;
		p_girl = index;
		//��ǰ������һ���С�к�
		for (int i = p_girl - 1; i >= 0; i--) {
			if (children[i] == boy && !flag[i]) {
				cout << i << ' ' << p_girl << endl;
				flag[i] = true;
				break;
			}
		}
	}
	queue();
}

int main() {
	cin.getline(children, length);
	queue();

	return 0;
}

