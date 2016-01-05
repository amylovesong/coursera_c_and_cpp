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
	for (int i = 2; i <= n / 2; i++) {
		for (; n2 % i == 0;) {
			n2 = n2 / i;
//			cout << i << "*";
			primeFactorSet.insert(i);
		}
	}
//	cout << "1" << endl;
	primeFactorMap.insert(make_pair(n, primeFactorSet.size()));
	return primeFactorSet.size();
}

bool customLess(const int a, const int b) {
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
		return customLess(a, b);
	}
};

class MyGreater: public greater<int> {
public:
	bool operator()(const int a, const int b) {
		return !customLess(a, b);
	}
};

int main() {
	priority_queue<int, vector<int>, MyLess> pqLess;
	priority_queue<int, vector<int>, MyGreater> pqGreater;
//	multiset<int, MyLess> ms;

	int num;
	cin >> num;
	int counter;
	int element;
	bool pushIntoPriorityHigh = true;
	while (num--) {
		counter = 10;
		while (counter--) {
			cin >> element;
			if (pushIntoPriorityHigh) {
				pqLess.push(element);
			} else {
				pqGreater.push(element);
			}
//			ms.insert(element);
		}
		int max, min;
		if (pushIntoPriorityHigh) {
			//先得到优先级最高的
			max = pqLess.top();
			pqLess.pop();
			//把剩下的元素依次出队到另一个优先队列（优先级低的在队头）中
			while (!pqLess.empty()) {
				pqGreater.push(pqLess.top());
				pqLess.pop();
			}
			//此时即可得到优先级最低的
			min = pqGreater.top();
			pqGreater.pop();
		} else {
			//先得到优先级最低的
			min = pqGreater.top();
			pqGreater.pop();
			//把剩下的元素依次出队到另一个优先队列（优先级高的在队头）中
			while (!pqGreater.empty()) {
				pqLess.push(pqGreater.top());
				pqGreater.pop();
			}
			//此时即可得到优先级最高的
			max = pqLess.top();
			pqLess.pop();
		}
		pushIntoPriorityHigh = !pushIntoPriorityHigh;

//		int min = *(ms.begin());
//		int max = *(--ms.end());
//		ms.erase(ms.begin());
//		ms.erase(--ms.end());
		cout << max << " " << min << endl;
	}

	return 0;
}

