/*
 * week6_exercise_distribute_wards.cpp
 *
 *  Created on: 2015年11月26日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
using namespace std;

void distribute(const int size, const float a, const char (*p_id)[4],
		const float (*p_degree)) {
	bool flag = false;
	int result_index[size];
	int count = 0;
	//找出重症病房里的病人信息，记录其索引值
	for (int i = 0; i < size; i++) {
		if (*(p_degree + i) > a) {
			result_index[count++] = i;
			flag = true;
		}
	}
	//根据记录的索引值，按严重程度排序
	int tmp = -1;
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1 - i; j++) {
			if (*(p_degree + result_index[j])
					< *(p_degree + result_index[j + 1])) {
				tmp = result_index[j];
				result_index[j] = result_index[j + 1];
				result_index[j + 1] = tmp;
			}
		}
	}
	//输出结果
	for (int i = 0; i < count; i++) {
		cout << *(p_id + result_index[i]) << ' ' << fixed << setprecision(1)
				<< *(p_degree + result_index[i]) << endl;
	}
	if (!flag) {
		cout << "None." << endl;
	}
}

int main() {
	int m = 0;
	float a = 0.0f;
	char id[50][4] = { '\0' };
	float degree[50] = { 0.0f };
	cin >> m >> a;
	for (int i = 0; i < m; i++) {
		cin >> *(id + i) >> *(degree + i);
	}

	distribute(m, a, id, degree);

	return 0;
}

