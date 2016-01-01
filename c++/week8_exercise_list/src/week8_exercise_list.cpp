/*
 * week8_exercise_list.cpp
 *
 *  Created on: 2016年1月1日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;

const bool debug = false;
const bool debug_testcase = true;
ifstream fin("testcase/in.txt", ios::in);
ofstream fout("testcase/myout.txt", ios::out);

const int MAX_LENGTH = 21;

const string OP_NEW = "new";
const string OP_ADD = "add";
const string OP_MERGE = "merge";
const string OP_UNIQUE = "unique";
const string OP_OUT = "out";

//vector<list<int> *> vec(10000);
list<int> * vec[10000];

string getOper(string oper) {
	return oper.substr(0, oper.find(' '));
}

string getArgvs(string line) {
	return line.substr(line.find(' ') + 1);
}

string showList(list<int> *pList) {
	string result = "";
	if (pList->size() > 0) {
		list<int>::const_iterator first = pList->begin();
		for (; first != pList->end(); first++) {
			stringstream ss;
			string tmp = "";
			ss << *first;
			ss >> tmp;
			result += (tmp + " ");
		}
	}
	return result;
}

void operation(string line) {
	if (debug) {
		cout << "line:" << line << endl;
	}
	string oper = getOper(line);
	string argvs = getArgvs(line);
	string argv1 = argvs.substr(0, argvs.find(' ')), argv2 = argvs.substr(
			argvs.find(' ') + 1);
	if (debug) {
		cout << "oper:" << oper << endl;
	}
	if (oper == OP_NEW) { //new id ——新建一个指定编号为id的序列(id<10000)
		if (debug) {
			cout << " argv1:" << argv1 << endl;
		}
		vec[atoi(argv1.c_str()) - 1] = new list<int>;
	} else if (oper == OP_ADD) { //add id num——向编号为id的序列加入整数num
		if (debug) {
			cout << " argv1:" << argv1 << " argv2:" << argv2 << endl;
		}
		list<int> * pList = vec[atoi(argv1.c_str()) - 1];
		pList->push_back(atoi(argv2.c_str()));
	} else if (oper == OP_MERGE) { //merge id1 id2——合并序列id1和id2中的数，并将id2清空
		list<int> * pList1 = vec[atoi(argv1.c_str()) - 1];
		list<int> * pList2 = vec[atoi(argv2.c_str()) - 1];
		pList1->merge(*pList2);
	} else if (oper == OP_UNIQUE) { //unique id——去掉序列id中重复的元素
		list<int> * pList = vec[atoi(argv1.c_str()) - 1];
//		if(debug_testcase){
//			line += "\r\n";
//			fout.write(line.c_str(), line.length());
//			string str = "before unique:" + showList(pList) + "\r\n";
//			fout.write(str.c_str(), str.length());
//		}
		pList->sort();
		pList->unique();
//		if(debug_testcase){
//			string str = "after unique:" + showList(pList) + "\r\n";
//			fout.write(str.c_str(), str.length());
//		}
	} else if (oper == OP_OUT) { //out id ——从小到大输出编号为id的序列中的元素，以空格隔开
		list<int> * pList = vec[atoi(argv1.c_str()) - 1];
		if (debug) {
			cout << " lst.size:" << pList->size() << endl;
		}
		string result = "";
		if(pList->size() > 0){
			pList->sort();
			result = showList(pList);
		}
		cout << result << endl;
		if (debug_testcase) {
//			line += "\r\n";
//			fout.write(line.c_str(), line.length());
			result += "\r\n";
			fout.write(result.c_str(), result.length());
		}
	}
}

int main() {
	char * tmp = new char[MAX_LENGTH];
	int n;
	if (debug_testcase) {
		fin.getline(tmp, MAX_LENGTH);
		n = atoi(tmp);
	} else {
		cin >> n;
	}
	string line = "";
	if (!debug_testcase) {
		cin.getline(tmp, MAX_LENGTH);
	}
	while (n > 0) {
		if (debug_testcase) {
//			cout << "n:" << n << endl;
			fin.getline(tmp, MAX_LENGTH);
		} else {
			cin.getline(tmp, MAX_LENGTH);
		}
		line = tmp;
		operation(line);

		n--;
	}
	delete[] tmp;
	fin.close();
	fout.close();

	return 0;
}

