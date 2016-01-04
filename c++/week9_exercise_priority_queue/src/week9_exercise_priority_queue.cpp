/*
 * week9_exercise_priority_queue.cpp
 *
 *  Created on: 2016年1月4日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <time.h>
using namespace std;

set<int> primeFactorSet;
typedef map<int, int> MII;
MII primeFactorMap;

int getPrimeFactorNumbers(int n) {
	MII::iterator p = primeFactorMap.find(n);
	if (p != primeFactorMap.end()) {
		return p->second;
	}
	primeFactorSet.clear();
	int n2 = n;
//	cout << n << "=";
	for (int i = 2; i < n; i++) {
		for (; n2 % i == 0;) {
			n2 = n2 / i;
//			cout << i << "*";
			primeFactorSet.insert(i);
		}
	}
//	cout << "1" << endl;
//	cout << "numbers:" << s.size() << endl;
	primeFactorMap.insert(make_pair(n, primeFactorSet.size()));
	return primeFactorSet.size();
}

bool compare(const int a, const int b){
	int pfnA = getPrimeFactorNumbers(a), pfnB = getPrimeFactorNumbers(b);
	if (pfnA == pfnB) {
		return a < b;
	} else {
		return pfnA < pfnB;
	}
}

class MyLess: public less<int> {
public:
	bool operator()(const int a, const int b) {
		return compare(a, b);
	}
};

class MyGreater: public greater<int>{
public:
	bool operator()(const int a, const int b) {
		return !compare(a, b);
	}
};

int main() {
	clock_t time = clock();
//	cout << "numbers:" << getPrimeFactorNumbers(30) << endl;
//	priority_queue<int, vector<int>, MyLess> pq;

//	ifstream cin("testcase\\in.txt");

	multiset<int, MyLess> ms;
	int num;
	cin >> num;
	int counter;
	int element;
	while (num--) {
		counter = 10;
		while (counter--) {
			cin >> element;
//			pq.push(element);
			ms.insert(element);
		}
//		int max = pq.top();
//		int min = 0;
//		pq.pop();
		int min = *(ms.begin());
		int max = *(--ms.end());
		ms.erase(ms.begin());
		ms.erase(--ms.end());
		cout << max << " " << min << endl;
	}

	time = clock() - time;
//	cout << "time:" << time << endl;
	return 0;
}

