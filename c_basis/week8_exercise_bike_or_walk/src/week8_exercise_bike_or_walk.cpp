/*
 * week8_exercise_bike_or_walk.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: sunxiaoling
 */
#include<iostream>
using namespace std;
int main() {
	int count = 0, distance = 0;
	int extra_time_bike = 27 + 23;
	double time_bike = 0, time_walk = 0;
	cin >> count;
	char result[count];
	for (int i = 0; i < count; i++) {
		cin >> distance;
		time_bike = distance / 3.0 + extra_time_bike;
		time_walk = distance / 1.2;
		if (time_bike < time_walk) {
			result[i] = 'B';
		} else if (time_bike > time_walk) {
			result[i] = 'W';
		} else {
			result[i] = 'A';
		}
	}
	for (int i = 0; i < count; i++) {
		if (result[i] == 'B') {
			cout << "Bike" << endl;
		} else if (result[i] == 'W') {
			cout << "Walk" << endl;
		} else if (result[i] == 'A') {
			cout << "All" << endl;
		}
	}
	return 0;
}

