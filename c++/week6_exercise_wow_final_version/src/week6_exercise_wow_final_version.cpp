/*
 * week6_exercise_wow_final_version.cpp
 *
 *  Created on: 2015年12月16日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
using namespace std;

//司令部
const string RED_HQ = "red", BLUE_HQ = "blue";
//武士的种类
const string ICEMAN = "iceman", LION = "lion", WOLF = "wolf", NINJA = "ninja",
		DRAGON = "dragon";
//武器的种类
const string SWORD = "sword", BOMB = "bomb", ARROW = "arrow";
const string WEAPONS[3] = { SWORD, BOMB, ARROW };

//旗帜
const string RED_FLAG = "red flag";
const string BLUE_FLAG = "blue flag";

const int INDEX_ICEMAN = 0, INDEX_LION = 1, INDEX_WOLF = 2, INDEX_NINJA = 3,
		INDEX_DRAGON = 4;

class Warrior {
private:
	string category;
	int id;
	int elements;
	int force;
public:
	Warrior(string category, int id, int elements, int force = 0) :
			category(category), id(id), elements(elements), force(force) {
		cout << this->category << " " << this->id << " born" << endl;
	}
	Warrior() {
		category = "";
		id = 0;
		elements = 0;
		force = 0;
	}
};

class Dragon: public Warrior {
	string weapon;
	float morale;
public:
	Dragon(int num, int elements, float morale, int force) :
			Warrior(DRAGON, num, elements, force) {
		weapon = WEAPONS[num % 3];
		this->morale = morale;
	}
	void showInfo() {
		cout << "It has a " << weapon << ",and it's morale is " << fixed
				<< setprecision(2) << morale << endl;
	}
};

class Ninja: public Warrior {
	string weapons[2];
public:
	Ninja(int num, int elements, int force) :
			Warrior(NINJA, num, elements, force) {
		weapons[0] = WEAPONS[num % 3];
		weapons[1] = WEAPONS[(num + 1) % 3];
	}
	void showInfo() {
		cout << "It has a " << weapons[0] << " and a " << weapons[1] << endl;
	}
};

class Iceman: public Warrior {
	string weapon;
public:
	Iceman(int num, int elements, int force) :
			Warrior(ICEMAN, num, elements, force) {
		weapon = WEAPONS[num % 3];
	}
	void showInfo() {
		cout << "It has a " << weapon << endl;
	}
};

class Lion: public Warrior {
	int loyalty;
public:
	Lion(int num, int elements, int loyalty, int force) :
			Warrior(LION, num, elements, force) {
		this->loyalty = loyalty;
	}
	void showInfo() {
		cout << "It's loyalty is " << loyalty << endl;
	}
};

class Wolf: public Warrior {
public:
	Wolf(int num, int elements, int force) :
			Warrior(WOLF, num, elements, force) {
	}
};

class City {
	int id;
	string flag;
	int elements;
	Warrior redWarrior();
	Warrior blueWarrior();
public:
	City(int id) :
			id(id) {
		flag = "";
		elements = 0;
	}
	City() {
		id = 0;
		flag = "";
		elements = 0;
	}
	void createElements() {
		elements += 10;
	}
};

class Headquarter {
	string name;
	int totalElements;
	bool stopped;

	int id;
	int createFlag;
	int index;
	const string *categoryOrder;
	const int *elementOrder;
	const int *forceOrder;
public:
	Headquarter(string name, int totalElements, const string *categoryOrder,
			const int *elementOrder, const int * forceOrder) :
			name(name), totalElements(totalElements), categoryOrder(
					categoryOrder), elementOrder(elementOrder), forceOrder(
					forceOrder) {
		stopped = false;

		id = 1;
		createFlag = 0;
		index = 0;
	}

	~Headquarter() {
	}

private:
	bool createWarrior(string category, int id, int element, int force) {
		if (totalElements < element) {
			return false;
		}
		cout << name << " ";
		totalElements -= element;
		if (category == DRAGON) {
			Dragon dragon(id, element, totalElements / (element * 1.0f), force);
			dragon.showInfo();
		} else if (category == NINJA) {
			Ninja ninja(id, element, force);
			ninja.showInfo();
		} else if (category == ICEMAN) {
			Iceman iceman(id, element, force);
			iceman.showInfo();
		} else if (category == LION) {
			Lion lion(id, element, totalElements, force);
			lion.showInfo();
		} else {
			Wolf wolf(id, element, force);
		}
		return true;
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
		if (createWarrior(categoryOrder[index], id, elementOrder[index],
				forceOrder[index])) {

		}

		//如果司令部中的生命元不足以制造某个按顺序应该制造的武士，则等待下一次

		return false;
	}
};

City * initCitys(City * citys, int amount) {
	for (int i = 0; i < amount; i++) {
		citys[i] = City(i + 1);
	}

	return citys;
}

int main() {
	int t; //测试数据的组数
	cin >> t;

	//测试数据有N组
	for (int i = 1; i <= t; i++) {
		int M, N, R, K, T;
		int E_dragon, E_ninja, E_iceman, E_lion, E_wolf;
		int F_dragon, F_ninja, F_iceman, F_lion, F_wolf;
		cin >> M >> N >> R >> K >> T;
		cin >> E_dragon >> E_ninja >> E_iceman >> E_lion >> E_wolf;
		cin >> F_dragon >> F_ninja >> F_iceman >> F_lion >> F_wolf;

		//红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。
		const string redCategory[5] = { ICEMAN, LION, WOLF, NINJA, DRAGON };
		const int redElement[5] =
				{ E_iceman, E_lion, E_wolf, E_ninja, E_dragon };
		const int redForce[5] = { F_iceman, F_lion, F_wolf, F_ninja, F_dragon };

		//蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。
		const string blueCategory[5] = { LION, DRAGON, NINJA, ICEMAN, WOLF };
		const int blueElement[5] =
				{ E_lion, E_dragon, E_ninja, E_iceman, E_wolf };
		const int blueForce[5] = { F_lion, F_dragon, F_ninja, F_iceman, F_wolf };

		City *citys = initCitys(citys, N);

		Headquarter redHeadquarter(RED_HQ, M, redCategory, redElement,
				redForce);
		Headquarter blueHeadquarter(BLUE_HQ, M, blueCategory, blueElement,
				blueForce);

		cout << "Case:" << i << endl;
		for (int time = 0; time <= T; time++) {
			switch (time % 60) {
			case 0://第0分，制造武士

				break;
			default:
				break;
			}
		}
	}

	return 0;
}

