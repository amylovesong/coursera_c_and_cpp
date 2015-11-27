/*
 * final_exam_judge_operator.cpp
 *
 *  Created on: 2015年11月27日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

const int MAX_LENGTH = 31;

int convertArray2Int(char str[]) {
	int num = 0;
	bool flag_negative = false;
	for (int i = 0; i < MAX_LENGTH - 1; i++) {
		if (str[i] == '\0') {
			break;
		}
		//考虑输入负数的情况
		if (str[i] == '-') {
			flag_negative = true;
		} else {
			//检查当前是否为最低位的数字
			if (str[i + 1] == '\0') {
				num += (str[i] - 48);
			} else {
				num = (num + (str[i] - 48)) * 10;
			}
		}
	}
	if (flag_negative) {
		num = -num;
	}

	return num;
}

void getNums(char input[MAX_LENGTH], int nums[]) {
	char temp[3][MAX_LENGTH] = { '\0' };
	int counter = 0;
	for (int i = 0; i < 3; i++) {
		int index = 0;
		while (input[counter] != '\0' && input[counter] != ',') {
			temp[i][index++] = input[counter++];
		}
		counter++;
		nums[i] = convertArray2Int(temp[i]);
	}
}

void judge(int nums[3]) {
	int a = nums[0], b = nums[1], c = nums[2];
	bool flag = false;

	//同时满足多个符号时，只认第一个
	if (c == (a + b)) {
		cout << '+' << endl;
		flag = true;
	} else if (c == (a - b)) {
		cout << '-' << endl;
		flag = true;
	} else if (c == (a * b)) {
		cout << '*' << endl;
		flag = true;
	} else if (b != 0) {
		if (c == (a / b)) {
			cout << '/' << endl;
			flag = true;
		} else if (c == (a % b)) {
			cout << '%' << endl;
			flag = true;
		}
	}
	if (!flag) {
		cout << "error" << endl;
	}
}

int main() {
	char input[MAX_LENGTH] = { '\0' };
	int nums[3] = { 0 };

	cin.getline(input, MAX_LENGTH);
	//从输入的字符串中提取三个操作数
	getNums(input, nums);
	judge(nums);

	return 0;
}

