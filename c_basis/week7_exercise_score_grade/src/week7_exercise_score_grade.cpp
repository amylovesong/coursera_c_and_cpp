/*
 * week7_score_grade.cpp
 *
 *  Created on: 2015年11月3日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int score = 0, grade = 0;
	cin >> score;
	if (score < 60) {
		grade = 7;
	} else if (score < 70) {
		grade = 6;
	} else if (score < 80) {
		grade = 5;
	} else if (score < 85) {
		grade = 4;
	} else if (score < 90) {
		grade = 3;
	} else if (score < 95) {
		grade = 2;
	} else {
		grade = 1;
	}
	cout << grade;
	return 0;
}

