/*
 * week10_part3.cpp
 *
 *  Created on: 2016年1月5日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;
// 在此处补充你的代码
typedef int (* pFunc)(int);
int sum(int a[], int length, pFunc sqr) {
	int sum = 0;
	for (int i = 0; i < length; i++) {
		sum += sqr(a[i]);
	}
	return sum;
}

int sqr(int n) {
	return n * n;
}

//int main() {
//	int t, n, a[0x100];
//	cin >> t;
//	for (int c = 0; c < t; ++c) {
//		cin >> n;
//		for (int i = 0; i < n; ++i)
//			cin >> a[i];
//		cout << sum(a, n, sqr) << endl;
//	}
//	return 0;
//}

