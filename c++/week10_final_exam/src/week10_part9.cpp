/*
 * week10_part9.cpp
 *
 *  Created on: 2016年1月6日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class A{
	string category;
	int age;
public:
	A(int age, string category="A"):category(category), age(age){ }
	virtual string getCategory(){
		return category;
	}
	virtual int getAge() const{
		return age;
	}
	virtual ~A(){ }
};

class B : public A{
public:
	B(int age):A(age, "B"){ }
};

struct Comp: public less<A *>{
public:
	bool operator()(const A* a, const A* b) const{
		return a->getAge() < b->getAge();
	}
};

void Print(A * a){
	cout << a->getCategory() << ' ' << a->getAge() << endl;
}

//int main() {
//
//	int t;
//	cin >> t;
//	set<A*, Comp> ct;
//	while (t--) {
//		int n;
//		cin >> n;
//		ct.clear();
//		for (int i = 0; i < n; ++i) {
//			char c;
//			int k;
//			cin >> c >> k;
//
//			if (c == 'A')
//				ct.insert(new A(k));
//			else
//				ct.insert(new B(k));
//		}
//		for_each(ct.begin(), ct.end(), Print);
//		cout << "****" << endl;
//	}
//}

