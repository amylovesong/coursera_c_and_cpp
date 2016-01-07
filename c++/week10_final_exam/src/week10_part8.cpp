/*
 * week10_part8.cpp
 *
 *  Created on: 2016年1月6日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <bitset>
using namespace std;

const int MAX = 32;

int main() {
	bitset<MAX> bs;
//	cout << bs.to_ulong() << endl;
	int t, n, i, j;
	cin >> t;
	while (t--) {
		bs.reset();
		cin >> n >> i >> j;
		//将n转换成二进制
		for (int index = 0; index < MAX; index++) {
			bs.set(index, n % 2);
			n /= 2;
			if (n == 0) {
				break;
			}
		}
		//输出整数k(按十六进制输出结果 )，k的第i位和n相同，第j位和n不同，i,j之间的位是1, 其他位都是0
		for (int index = 0; index < MAX; index++) {
			if (index < i) {
				bs.set(index, 0);
			} else if (index > i && index < j) {
				bs.set(index, 1);
			} else if (index == j) {
				bs.flip(index);
			} else {
				if (index != i) {//第i位不变
					bs.set(index, 0);
				}
			}
		}

//		cout << bs.to_string() << endl;
		cout << hex << bs.to_ulong() << endl;
	}

	return 0;
}

