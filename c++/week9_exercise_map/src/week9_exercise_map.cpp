/*
 * week9_exercise_map.cpp
 *
 *  Created on: 2016年1月3日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <map>
#include <cstdio>
using namespace std;

int main() {
	typedef multimap<int, int> MII;
	MII members;
	members.insert(make_pair(1000000000, 1));

	int n;
	scanf("%d", &n);
	int newid, newValue;
	while (n--) {
		scanf("%d %d", &newid, &newValue);
		MII::iterator newOne = members.insert(make_pair(newValue, newid));
		MII::iterator selected;
		if (newOne == members.begin()) {
			newOne++;
			selected = newOne;
		} else if (newOne == members.end()) {
			newOne--;
			selected = newOne;
		} else {
			MII::iterator pre = --newOne;
			newOne++;
			newOne++;
			MII::iterator next = newOne;

			selected = pre;//优先用前面的
			if (next->first - newValue < newValue - pre->first) {//只有当后面的比前面的离当前更近，才用后面的
				selected = next;
			}
		}
		printf("%d %d\n", newid, selected->second);
	}

	return 0;
}
