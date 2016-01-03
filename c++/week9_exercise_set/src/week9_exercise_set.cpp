/*
 * week9_exercise_set.cpp
 *
 *  Created on: 2016年1月3日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <set>
using namespace std;

int main() {
	multiset<int> ms;
	set<int> s;
	int n;
	cin >> n;
	string cmd;
	int num;
	while (n--) {
		cin >> cmd >> num;
//		cout << "test cmd:" << cmd << " num:" << num << endl;
		if (cmd == "add") { //add x 把x加入集合，输出操作后集合中x的个数
			ms.insert(num);
			s.insert(num);
			cout << ms.count(num) << endl;
		} else if (cmd == "ask") { //ask x 对集合中元素x的情况询问，先输出0或1表示x是否曾被加入集合（0表示不曾加入），再输出当前集合中x的个数，中间用空格格开。
			cout << s.count(num);
			cout << " " << ms.count(num) << endl;
		} else if (cmd == "del") { //del x 把集合中所有与x相等的元素删除，输出操作前集合中x的个数
			cout << ms.count(num) << endl;
			ms.erase(ms.lower_bound(num), ms.upper_bound(num));
		}
	}

	return 0;
}

