/*
 * week2_exercise_invoice.cpp
 *
 *  Created on: 2015年11月12日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
using namespace std;

float money_id[3] = { 0.0f }, money_category[3] = { 0.0f };

void calculate_money(int id, int num) {
	char category = '\0';
	float money = 0.0f;
	for (int i = 0; i < num; i++) {
		cin >> category >> money;
		money_id[id - 1] += money;
		switch (category) {
		case 'A':
			money_category[0] += money;
			break;
		case 'B':
			money_category[1] += money;
			break;
		case 'C':
			money_category[2] += money;
			break;
		}
	}
}

void cout_result(){
	cout << fixed << setprecision(2);
	for (int i = 0; i < 3; i++) {
		cout << i + 1 << ' ' << money_id[i] << endl;
	}
	for (int i = 0; i < 3; i++) {
		cout << (char) (i + 65) << ' ' << money_category[i] << endl;
	}
}

int main() {
	for (int counter = 0; counter < 3; counter++) {
		int id = 0, num = 0;
		cin >> id >> num;
		calculate_money(id, num);
	}
	cout_result();

	return 0;
}

