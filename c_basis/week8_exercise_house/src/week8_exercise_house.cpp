/*
 * week8_exercise_house.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: sunxiaoling
 */
#include<iostream>
using namespace std;
int main() {
	int N = 0, K = 0, year = 1;
	double price = 200;
	while (cin >> N >> K) {
		year = 1, price = 200; //initial value
		while (true) {
			if (year > 20) {
				cout << "Impossible" << endl;
				break;
			} else if (N * year >= price) {
				cout << year << endl;
				break;
			}
			year++;
			price = price * (1 + K / 100.0);
		}
	}

	return 0;
}

