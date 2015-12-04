/*
 * week2_exercise_student.cpp
 *
 *  Created on: 2015Äê12ÔÂ3ÈÕ
 *      Author: sunxiaoling
 */

#include <iostream>
#include <stdio.h>
using namespace std;

class Student {
private:
	string sName;
	int sAge;
	string sNum;
	int *sScores;
public:
	void setName(string name);
	string getName();
	void setAge(int age);
	int getAge();
	void setNum(string num);
	string getNum();
	void setScores(int scores[]);
	int getAverageScore();
};

void Student::setName(string name) {
	sName = name;
}

string Student::getName() {
	return sName;
}

void Student::setAge(int age) {
	sAge = age;
}

int Student::getAge() {
	return sAge;
}

void Student::setNum(string num) {
	sNum = num;
}

string Student::getNum() {
	return sNum;
}

void Student::setScores(int scores[]) {
	sScores = scores;
}

int Student::getAverageScore() {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += sScores[i];
	}
	return sum / 4;
}

int main() {
	char name[20];
	int age;
	char num[20];
	int scores[4];
	scanf("%[^,],%d,%[^,],%d,%d,%d,%d", name, &age, num, &scores[0], &scores[1],
			&scores[2], &scores[3]);
//	cout << "name: " << name << " age: " << age << endl;
//	cout << "num: " << num << " scores: " << scores[0] << " " << scores[1]
//			<< " " << scores[2] << " " << scores[3] << endl;

	Student student;
	student.setName(name);
	student.setAge(age);
	student.setNum(num);
	student.setScores(scores);
	cout << student.getName() << ',' << student.getAge() << ','
			<< student.getNum() << ',' << student.getAverageScore() << endl;

	return 0;
}

