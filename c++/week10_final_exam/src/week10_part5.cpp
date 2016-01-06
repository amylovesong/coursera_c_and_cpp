/*
 * week10_part5.cpp
 *
 *  Created on: 2016年1月5日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class CMy_add {
	int & sum;
public:
	CMy_add(int & num) : sum(num) { }
	void operator()(int value) {
//		cout << "value:" << value;
		//二进制低3位：即八进制的最低位
		sum += value % 8;
//		int remainder = 0;
//		for (int i = 0; i < 3; i++) {
//			remainder = value % 2;
//			if(remainder > 0){
//				for(int j=0; j < i; j++){
//					remainder *= 2;
//				}
//			}
//			sum += remainder;
//			if (value / 2 == 0) {
//				break;
//			} else {
//				value = value / 2;
//			}
//		}
//		cout << " sum:" << sum << endl;
	}
};

//int main(int argc, char* argv[]) {
//	int v, my_sum = 0;
//	vector<int> vec;
//	cin >> v;
//	while (v) {
//		vec.push_back(v);
//		cin >> v;
//	}
//	for_each(vec.begin(), vec.end(), CMy_add(my_sum));
//	cout << my_sum << endl;
//	return 0;
//}

