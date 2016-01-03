/*
 * week9_exercise_map.cpp
 *
 *  Created on: 2016年1月3日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <map>
using namespace std;

int main() {
	typedef multimap<int, int> MII;
	MII members;
	members.insert(make_pair(1000000000, 1));

	int n;
	cin >> n;
	int newid, newValue;
	while (n--) {
		cin >> newid >> newValue;
		members.insert(make_pair(newValue, newid));
		MII::iterator selected;
		MII::iterator lp = members.lower_bound(newValue);
		MII::iterator up = members.upper_bound(newValue);
		if (lp == members.begin()) {
			selected = up;
		} else {
			lp--;
			selected = lp;
			if (up->first - newValue < newValue - lp->first) {
				selected = up;
			}
		}
		cout << newid << ' ' << selected->second << endl;
	}

	return 0;
}
