/*
 * week10_part2.cpp
 *
 *  Created on: 2016年1月5日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;
class Number {
public:
    int num;
    Number(int n): num(n) {
    }
// 在此处补充你的代码
    int & value(){
    	return this->num;
    }
    void operator+(Number & b){
    	this->num += b.num;
    }
};
//int main() {
//    Number a(2);
//    Number b = a;
//    cout << a.value() << endl;
//    cout << b.value() << endl;
//    a.value() = 8;
//    cout << a.value() << endl;
//    a+b;
//    cout << a.value() << endl;
//    return 0;
//}


