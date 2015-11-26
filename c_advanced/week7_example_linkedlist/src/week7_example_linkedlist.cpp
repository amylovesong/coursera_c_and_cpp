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
	student *head, *temp;
	int num, n = 0;
	head = new student;
	temp = head;
	cin >> num;
	while (num != -1) {
		n++;
		temp->id = num;
		temp->next = new student;
		temp = temp->next;
		cin >> num;
	}
	if (n == 0) {
		head = NULL;
	} else {
		temp->next = NULL;
	}
	return head;
}

int main() {
	student *head = create();
	if (head != NULL) {
		cout << "The first id of linkedlist is " << head->id << endl;
	} else {
		cout << "The linkedlist is empty." << endl;
	}
	return 0;
}

