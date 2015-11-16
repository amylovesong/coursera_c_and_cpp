/*
 * week2_exercise_next_day.cpp
 *
 *  Created on: 2015年11月16日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <stdio.h>
using namespace std;

bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main() {
	int day_of_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	bool flag_new_year = false, flag_new_month = false, flag_next_day = false;
	int year = 0, month = 0, day = 0;
	scanf("%d-%d-%d", &year, &month, &day);

	if (month == 12 && day == 31) {
		flag_new_year = true;
	} else if (month == 2 && (day == 28 || day == 29)) {
		if (isLeapYear(year)) { //闰年
			if (day == 29) {
				flag_new_month = true;
			} else {
				flag_next_day = true;
			}
		} else {
			if (day == 28) {
				flag_new_month = true;
			}
		}
	} else {
		int max_day = day_of_month[month - 1];
		if (day >= max_day) {
			flag_new_month = true;
		} else {
			flag_next_day = true;
		}
	}

	if (flag_new_year) {
		printf("%d-%02d-%02d\n", (year + 1), 1, 1);
	} else if (flag_new_month) {
		printf("%d-%02d-%02d\n", year, (month + 1), 1);
	} else if (flag_next_day) {
		printf("%d-%02d-%02d\n", year, month, (day + 1));
	}

	return 0;
}

