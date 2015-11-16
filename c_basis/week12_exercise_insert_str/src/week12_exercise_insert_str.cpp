/*
 * week12_exercise_insert_str.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: sunxiaoling
 */

#include<iostream>
using namespace std;
int main() {
	char str[11] = { '\0' }, substr[4] = { '\0' };
	while (cin >> str >> substr) {
		char result[14] = { '\0' };
//		cout << str << "---" << substr << endl;
		char max = '\0';
		int max_index = 0;
		int i = 0;
		while (str[i] != '\0') {
			if (max < str[i]) {
				max = str[i];
				max_index = i;
			}
			i++;
		}
//		cout << "max=" << max << " index=" << max_index << endl;
		int j = 0, k = 0;
		while (j <= max_index) {
			result[j] = str[j];
			j++;
		}
//		cout << "j:" << j << " result:" << result << endl;
		while (substr[k] != '\0') {
			result[j] = substr[k];
			k++;
			j++;
		}
//		cout << "j:" << j << " result:" << result << endl;
		k = max_index + 1;
//		cout << "K:" << k << endl;
		while (str[k] != '\0') {
//			cout << "K:" << k << " str[k]:" << str[k] << endl;
			result[j] = str[k];
			j++;
			k++;
//			cout << "result:" << result << endl;
		}
		cout << result << endl;
	}

	return 0;
}

