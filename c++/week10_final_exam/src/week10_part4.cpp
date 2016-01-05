/*
 * week10_part4.cpp
 *
 *  Created on: 2016年1月5日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;
// 在此处补充你的代码
class CType{
	int value;
public:
	void setvalue(int n){
		value = n;
	}
	int operator++(int n){//后置运算符作为二元运算符重载，多写一个参数，具体无意义
		int cur = value;
		value *= value;
		return cur;
	}
	friend ostream & operator<<(ostream & o, const CType & obj){
		o << obj.value;
		return o;
	}
};

//int main(int argc, char* argv[]) {
//	CType obj;
//	int n;
//	cin >> n;
//	while (n) {
//		obj.setvalue(n);
//		cout << obj++ << " " << obj << endl;
//		cin >> n;
//	}
//	return 0;
//}


