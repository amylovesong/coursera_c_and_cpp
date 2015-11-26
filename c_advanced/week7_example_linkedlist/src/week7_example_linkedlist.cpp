/*
 * week7_example_linkedlist.cpp
 *
 *  Created on: 2015年11月26日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

struct student {
	int id;
	student *next;
};

student *create() {
	student *head = NULL, *temp = NULL;
	int num;
//	, n = 0;
//	head = new student;
//	temp = head;
	cin >> num;
	while (num != -1) {
		if (head == NULL) {
			head = new student;
			temp = head;
		} else {
			temp->next = new student;
			temp = temp->next;
		}
//		n++;
		temp->id = num;
		cin >> num;
	}
//	if (n == 0) {
//		head = NULL;
//	} else {
	if (temp != NULL) {
		temp->next = NULL;
	}
	return head;
}

student *dele(student *head, int n) {
	student *temp, *follow;
	temp = head;
	if (head == NULL) { //空表
		return head;
	}
	if (head->id == n) { //第一个节点是要删除的目标
		head = head->next;
		delete temp;
		return head;
	}
	while (temp != NULL && temp->id != n) { //寻找要删除的目标
		follow = temp;
		temp = temp->next;
	}
	if (temp == NULL) { //没寻到要删除的目标
		cout << "not found";
	} else {
		follow->next = temp->next; //删除目标节点
		delete temp;
	}
	return head;
}

student *insert(student *head, int n) {
	student *temp, *unit, *follow;
	temp = head;
	unit = new student;
	unit->id = n;
	unit->next = NULL;
	if (head == NULL) { //空表，则新插入的元素为第一个
		head = unit;
		return head;
	}
	//寻找第一个不小于n或结尾的节点temp
	while (temp->next != NULL && temp->id < n) {
		follow = temp;
		temp = temp->next;
	}
	if (temp == head) { //如果temp为第一个节点
		unit->next = head;
		head = unit;
	} else {
		//temp为最后一个节点，并且新插入的节点在temp的后面
		if (temp->next == NULL && temp->id < n) {
			temp->next = unit;
		} else { //新插入的节点在follow与temp中间
			unit->next = temp;
			follow->next = unit;
		}
	}
	return head;
}

void show_linkedlist(const student *head) {
	if (head == NULL) {
		cout << "The linkedlist is empty." << endl;
	} else {
		while (head->next != NULL) {
			cout << head->id << endl;
			head = head->next;
		}
		cout << head->id << endl;
	}
}

int main() {
	// Test case:
	// 122
	// 123
	// 125
	// 126
	// -1

	student *head = create();
	cout << "create:" << endl;
	show_linkedlist(head);

	head = dele(head, 123);
	cout << "delete 123:" << endl;
	show_linkedlist(head);

	head = dele(head, 122);
	cout << "delete 122:" << endl;
	show_linkedlist(head);

	head = dele(head, 126);
	cout << "delete 126:" << endl;
	show_linkedlist(head);

	head = insert(head, 121);
	cout << "insert 121:" << endl;
	show_linkedlist(head);

	head = insert(head, 124);
	cout << "insert 124:" << endl;
	show_linkedlist(head);

	head = insert(head, 127);
	cout << "insert 127:" << endl;
	show_linkedlist(head);

	return 0;
}

