/*
 * week7_exercise_int.cpp
 *
 *  Created on: 2015年12月24日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	int num;
	cin >> num;
	cout << setbase(16) << num << endl;
	cout << setbase(10) << setfill('0') << setw(10) << num << endl;

	return 0;
}


