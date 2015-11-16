/*
 * week12_exercise_simple_calculator.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int num1 = 0, num2 = 0;
	char op = '\0';
	cin >> num1 >> num2 >> op;
	switch (op) {
	case '+':
		cout << (num1 + num2);
		break;
	case '-':
		cout << (num1 - num2);
		break;
	case '*':
		cout << (num1 * num2);
		break;
	case '/':
		if (num2 == 0) {
			cout << "Divided by zero!";
		} else {
			cout << (num1 / num2);
		}
		break;
	default:
		cout << "Invalid operator!";
	}
	cout << endl;

	return 0;
}

