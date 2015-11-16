/*
 * week7_exercise_max_k.cpp
 *
 *  Created on: 2015年11月3日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	int n = 0, k = 0;
	cin >> n;
	cin >> k;
	int num[n];
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	int max = 0, min = 0, max_index = 0;
	for (int i = 0; i < k; i++) { //循环K次找第K个最大数
		//初始化最大值和最小值为第一个数
		max = num[0], min = num[0], max_index = 0;
		for (int j = 1; j < n; j++) {
			if (max < num[j]) {
				max = num[j];
				max_index = j;
			}
			if (min > num[j]) {
				min = num[j];
			}
			//cout << "j:" << j << "--min:" << min << "--max:" << max << endl;
		}
		//每次循环结束，找到当前数组中的最大数和最小数，并记录最大数的index
		//并用最小数替换数组中的最大数，以确保下一次循环结束找到的是第i大的数
		num[max_index] = min;
//		cout << "i:" << i << "--max:" << max << "--max_index:" << max_index
//				<< endl;
	}
	//外层循环结束后的最大数max即为第K大的数
	cout << max << endl;
	return 0;
}

