/*
 * final_exam_point.cpp
 *
 *  Created on: 2015年11月29日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

struct point {
	int x;
	int y;
};

void sort(point res[], int length) {
	point temp;
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1 - i; j++) {
			if (res[j].x > res[j + 1].x) {
				temp = res[j];
				res[j] = res[j + 1];
				res[j + 1] = temp;
			}
		}
	}
}

void func(point points[], int length) {
	point res[100];
	int count = 0;
	for (int i = 0; i < length; i++) {
		bool flag = true;
		point cur = points[i];
		//对于当前要检查的点，遍历整个集合，只要有一个点比它大，则它不是极大点
		for (int j = 0; j < length; j++) {
			if (i != j) {
				if (points[j].x >= cur.x && points[j].y >= cur.y) {
					flag = false;
					break;
				}
			}
		}
		//遍历完整个集合，如果没有任何一个点比当前点的坐标大，那么它就是极大点
		if (flag) {
			res[count++] = cur;
		}
	}
	//对找到的所有极大点，按照x坐标从小到大的顺序进行排序
	sort(res, count);

	for (int i = 0; i < count; i++) {
		cout << '(' << res[i].x << ',' << res[i].y << ')';
		if (i < count - 1) {
			cout << ',';
		}
	}
	cout << endl;
}

int main() {
	point points[100];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> points[i].x >> points[i].y;
	}
	func(points, n);

	return 0;
}

