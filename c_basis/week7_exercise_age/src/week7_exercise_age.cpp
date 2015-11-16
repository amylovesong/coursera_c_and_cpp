/*
 * week7_exercise_age.cpp
 *
 *  Created on: 2015年11月3日
 *      Author: sunxiaoling
 */

#include<iostream>
#include<iomanip>
using namespace std;
int main() {
	int n = 0, age = 0;
	int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> age;
		if (age <= 18) {
			n1++;
		} else if (age <= 35) {
			n2++;
		} else if (age <= 60) {
			n3++;
		} else {
			n4++;
		}
	}
	float f = (float) n1 / n * 100;
	cout << "1-18: " << fixed << setprecision(2) << f << '%' << endl;
	f = (float) n2 / n * 100;
	cout << "19-35: " << f << '%' << endl;
	f = (float) n3 / n * 100;
	cout << "36-60: " << f << '%' << endl;
	f = (float) n4 / n * 100;
	cout << "60-: " << f << '%' << endl;
	return 0;
}

