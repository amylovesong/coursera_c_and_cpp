/*
 * week3_exercise_wow_prepare_for_battle.cpp
 *
 *  Created on: 2015年12月7日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
using namespace std;

const string RED_HQ = "red", BLUE_HQ = "blue";
const string ICEMAN = "iceman", LION = "lion", WOLF = "wolf", NINJA = "ninja",
		DRAGON = "dragon";

const int INDEX_ICEMAN = 0, INDEX_LION = 1, INDEX_WOLF = 2, INDEX_NINJA = 3,
		INDEX_DRAGON = 4;

class Warrior {
private:
	string category;
	int num;
	int health;
	int attack;
public:
	Warrior(string category, int num, int health, int attack = 0) :
			category(category), num(num), health(health), attack(attack) {
		cout << category << " " << num << " born with strength " << health;
	}
};

class Headquarter {
private:
	string name;
	int lifeValue;
	bool stopped;
	int *counter;

	int num;
	int createFlag;
	int index;
	const string *categorys;
	const int *HPs;
public:
	Headquarter(string name, int lifeValue, const string *categorys,
			const int *HPs) :
			name(name), lifeValue(lifeValue), categorys(categorys), HPs(HPs) {
		stopped = false;
		counter = new int[5];
		for (int i = 0; i < 5; i++) {
			counter[i] = 0;
		}

		num = 1;
		createFlag = 0;
		index = 0;
	}

	~Headquarter() {
		delete[] counter;
	}

private:
	bool createWarrior(string category, int num, int health) {
		if (lifeValue < health) {
			return false;
		}
		cout << name << " ";
		Warrior w = Warrior(category, num, health);
		lifeValue -= health;
		cout << ",";
		counter4Category(category);
		cout << endl;
		return true;
	}

	void counter4Category(string category) {
		int index = -1;
		if (category == ICEMAN) {
			index = INDEX_ICEMAN;
		} else if (category == LION) {
			index = INDEX_LION;
		} else if (category == WOLF) {
			index = INDEX_WOLF;
		} else if (category == NINJA) {
			index = INDEX_NINJA;
		} else if (category == DRAGON) {
			index = INDEX_DRAGON;
		}
		if (index == -1) {
			return;
		}
		counter[index]++;
		cout << counter[index] << " " << category << " in " << name
				<< " headquarter";
	}

	void stop() {
		stopped = true;
		cout << name << " headquarter stops making warriors" << endl;
	}

public:
	bool isStopped() {
		return stopped;
	}

	bool createWarriorsByOrder() {
		//当成功制造某个武士时，reset flag
		if (createWarrior(categorys[index], num, HPs[index])) {
			createFlag = 0;
			num++;
		} else {
			createFlag++;
		}
		if (index >= 4) {
			index = 0;
		} else {
			index++;
		}

		//如果司令部中的生命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。
		if (createFlag > 0 && createFlag < 5) {
			return true;
		}
		//所有武士都不能制造了
		if (createFlag >= 5) {
			stop();
			return false;
		}
		//当前武士制造成功
		return false;
	}
};

int main() {
	int n;
	cin >> n;

	//测试数据有N组
	for (int i = 1; i <= n; i++) {
		int m;
		int hp_dragon, hp_ninja, hp_iceman, hp_lion, hp_wolf;
		cin >> m;
		cin >> hp_dragon >> hp_ninja >> hp_iceman >> hp_lion >> hp_wolf;

		//红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。
		const string redCategory[5] = { ICEMAN, LION, WOLF, NINJA, DRAGON };
		const int redHP[5] =
				{ hp_iceman, hp_lion, hp_wolf, hp_ninja, hp_dragon };

		//蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。
		const string blueCategory[5] = { LION, DRAGON, NINJA, ICEMAN, WOLF };
		const int blueHP[5] =
				{ hp_lion, hp_dragon, hp_ninja, hp_iceman, hp_wolf };

		Headquarter redHeadquarter(RED_HQ, m, redCategory, redHP);
		Headquarter blueHeadquarter(BLUE_HQ, m, blueCategory, blueHP);

		cout << "Case:" << i << endl;
		int time = 0;
		while (true) {
			//红方
			if (!redHeadquarter.isStopped()) {
				cout << setfill('0') << setw(3) << time << " ";
				//成功制造当前武士，或者停止制造，由蓝方继续
				while (redHeadquarter.createWarriorsByOrder()) {

				}
			}
			//蓝方
			if (!blueHeadquarter.isStopped()) {
				cout << setfill('0') << setw(3) << time << " ";
				//成功制造当前武士，或者停止制造，由红方继续
				while (blueHeadquarter.createWarriorsByOrder()) {

				}
			}
			//如果两方都停止制造，则结束
			if (redHeadquarter.isStopped() && blueHeadquarter.isStopped()) {
				break;
			} else {
				time++;
			}
		}
	}

	return 0;
}

