/*
 * week6_exercise_wow_final_version.cpp
 *
 *  Created on: 2015年12月16日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
using namespace std;

const bool debug = true;

//司令部
const string RED_HQ = "red", BLUE_HQ = "blue";
int RED_HQ_CITY_ID = 0, BLUE_HQ_CITY_ID = 0;
//武士的种类
const string ICEMAN = "iceman", LION = "lion", WOLF = "wolf", NINJA = "ninja",
		DRAGON = "dragon";
//武器的种类
const string SWORD = "sword", BOMB = "bomb", ARROW = "arrow";
const string WEAPONS[3] = { SWORD, BOMB, ARROW };
int R = 0;

//旗帜
const string RED_FLAG = "red flag";
const string BLUE_FLAG = "blue flag";

const int INDEX_ICEMAN = 0, INDEX_LION = 1, INDEX_WOLF = 2, INDEX_NINJA = 3,
		INDEX_DRAGON = 4;

void showFormatTime(int time) {
	cout << setfill('0') << setw(3) << time / 60 << ':' << setw(2) << time % 60
			<< ' ';
}

class Weapon {
protected:
	int num; //武器的编号
	string category; //武器的类型
public:
	Weapon(int num, string category) :
			num(num), category(category) {
	}
	string getCategory() {
		return category;
	}
};

class Sword: public Weapon {
	int force;
public:
	Sword(int force = 0) :
			Weapon(0, SWORD), force(force) {
	}
	void setForce(int force) {
		this->force = force;
	}
	int getForce() {
		return force;
	}
	bool canUse() {
		return force > 0;
	}
	void afterBattle() {
		force = force * 4 / 5; //每经过一次战斗(不论是主动攻击还是反击)，就会变钝，攻击力变为本次战斗前的80% (去尾取整)
	}
};

class Bomb: public Weapon {
public:
	Bomb() :
			Weapon(1, BOMB) {
	}
};

class Arrow: public Weapon {
	int R;
	int useTimes;
public:
	Arrow(int R) :
			Weapon(2, ARROW), R(R), useTimes(3) {
	}
	int getR() {
		return R;
	}
	bool canUse() { //使用3次后即被耗尽
		return useTimes > 0;
	}
	void afterBattle() {
		useTimes--;
	}
};

Weapon * createWeapon(int num) {
	Weapon * weapon;
	switch (num % 3) {
	case 0:
		weapon = new Sword();
		break;
	case 1:
		weapon = new Bomb();
		break;
	case 2:
		weapon = new Arrow(R);
		break;
	}
	return weapon;
}

class Warrior {
protected:
	string category;
	int num;
	int elements;
	int force;
	string hqName; //武士所属的司令部
	int cityId; //武士当前所处的城市的id，移动时更新
public:
	Warrior(string category, int num, int elements, int force, string hqName,
			int cityId) :
			category(category), num(num), elements(elements), force(force), hqName(
					hqName), cityId(cityId) {
		cout << this->category << ' ' << this->num << " born" << endl;
	}
//	Warrior() :
//			category(""), num(0), elements(0), force(0), hqName(""), cityId(0) {
//	}
	void init(string category, int num, int elements, int force, string hqName,
			int cityId) {
		this->category = category;
		this->num = num;
		this->elements = elements;
		this->force = force;
		this->hqName = hqName;
		this->cityId = cityId;
	}
	~Warrior() {
		if (debug) {
			cout << "test ~Warrior() " << hqName << " num:" << num << endl;
		}
	}
	string getCategory() {
		return category;
	}
	string gethqName() {
		return hqName;
	}
	int getCityId() {
		return cityId;
	}
};

class Dragon: public Warrior {
	Weapon * weapon;
	float morale;
public:
	Dragon(int num, int elements, float morale, int force, string hqName,
			int cityId) :
			Warrior(DRAGON, num, elements, force, hqName, cityId), morale(
					morale) {
		weapon = createWeapon(num % 3);
		if (weapon->getCategory() == SWORD) {
			((Sword *) weapon)->setForce(force / 5);
		}
		cout << "Its morale is " << fixed << setprecision(2) << morale << endl;
	}
	~Dragon() {
		if (weapon) {
			delete weapon;
		}
	}
	void showInfo() {
		cout << "It has a " << weapon << endl;
	}
};

class Ninja: public Warrior {
	Weapon weapons[2];
public:
	Ninja(int num, int elements, int force, string hqName, int cityId) :
			Warrior(NINJA, num, elements, force, hqName, cityId) {
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
	Iceman(int num, int elements, int force, string hqName, int cityId) :
			Warrior(ICEMAN, num, elements, force, hqName, cityId) {
		weapon = WEAPONS[num % 3];
	}
	void showInfo() {
		cout << "It has a " << weapon << endl;
	}
};

class Lion: public Warrior {
	int loyalty;
public:
	Lion(int num, int elements, int loyalty, int force, string hqName,
			int cityId) :
			Warrior(LION, num, elements, force, hqName, cityId) {
		this->loyalty = loyalty;
		cout << "It's loyalty is " << loyalty << endl;
	}
	void showInfo() {
		cout << "It's loyalty is " << loyalty << endl;
	}
	void runAway() {
		cout << hqName << " lion " << num << " ran away" << endl;
	}
	int getLoyalty() {
		return loyalty;
	}
};

class Wolf: public Warrior {
public:
	Wolf(int num, int elements, int force, string hqName, int cityId) :
			Warrior(WOLF, num, elements, force, hqName, cityId) {
	}
};

class City {
	int id;
	string flag;
	int elements;
	Warrior * redWarrior;
	Warrior * blueWarrior;
public:
	City(int id) :
			id(id), flag(""), elements(0), redWarrior(NULL), blueWarrior(NULL) {
		if (debug) {
			cout << "test City(int id) id:" << id << endl;
		}
	}
	City() :
			id(0), flag(""), elements(0), redWarrior(NULL), blueWarrior(NULL) {
		if (debug) {
			cout << "test City()" << endl;
		}
	}
	~City() {
		if (debug) {
			cout << "test ~City() id:" << id << endl;
		}
	}
	void setId(int id) {
		this->id = id;
	}
	int getId() {
		return id;
	}
	void setFlag(string flag) {
		this->flag = flag;
	}
	string getFlag() {
		return flag;
	}
	void createElements() {
		elements += 10;
	}
	int getElements() { //生命元被取走
		const int e = elements;
		elements = 0;
		return e;
	}
	void setRedWarrior(Warrior * red) {
		this->redWarrior = red;
	}
	void setBlueWarrior(Warrior * blue) {
		this->blueWarrior = blue;
	}
};

class Headquarter {
	string name;
	int totalElements;
	int cityId;
	Warrior ** warriors;
//	Warrior * warriors[100];

	int warriorId;
	int index;
	const string *categoryOrder;
	const int *elementOrder;
	const int *forceOrder;
public:
	Headquarter(string name, int totalElements, int cityId,
			const string *categoryOrder, const int *elementOrder,
			const int * forceOrder) :
			name(name), totalElements(totalElements), cityId(cityId), categoryOrder(
					categoryOrder), elementOrder(elementOrder), forceOrder(
					forceOrder) {
		warriors = new Warrior *[100];
		for (int i = 0; i < 100; i++) {
			warriors[i] = NULL;
		}

		warriorId = 1;
		index = 0;
	}

	~Headquarter() {
		if (debug) {
			cout << "test ~Headquarter() " << name << endl;
		}
		for (int i = 0; i < 100; i++) {
			if (warriors[i]) {
				delete warriors[i];
				warriors[i] = NULL;
			}
		}
		delete[] warriors;
	}
private:
	bool createWarrior(int time, string category, int id, int element,
			int force) {
		//如果司令部中的生命元不足以制造某个按顺序应该制造的武士，则等待下一次
		if (debug) {
			cout << "test " << name << " createWarrior() " << category << " id:"
					<< id << " totalElements:" << totalElements << " element:"
					<< element << endl;
		}
		if (totalElements < element) {
			return false;
		}
		showFormatTime(time);
		cout << name << " ";
		totalElements -= element;
		if (category == DRAGON) {
			warriors[id - 1] = new Dragon(id, element,
					totalElements / (element * 1.0f), force, name, cityId);
		} else if (category == NINJA) {
			warriors[id - 1] = new Ninja(id, element, force, name, cityId);
		} else if (category == ICEMAN) {
			warriors[id - 1] = new Iceman(id, element, force, name, cityId);
		} else if (category == LION) {
			warriors[id - 1] = new Lion(id, element, totalElements, force, name,
					cityId);
		} else {
			warriors[id - 1] = new Wolf(id, element, force, name, cityId);
		}
		return true;
	}
public:
	bool createWarriorsByOrder(int time) {
		//按顺序制造
		if (createWarrior(time, categoryOrder[index], warriorId,
				elementOrder[index], forceOrder[index])) {
			index = index == 4 ? 0 : index + 1; //从0到4循环
			warriorId++;
			return true;
		}
		return false;
	}
	void lionRunAway(int time) {
		//已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑
		int enemyHQId = -1;
		if (name == RED_HQ) {
			enemyHQId = BLUE_HQ_CITY_ID;
		} else {
			enemyHQId = RED_HQ_CITY_ID;
		}
		for (int i = 0; i < warriorId; i++) {
			if (warriors[i] && warriors[i]->getCategory() == LION) {
				Lion * lion = (Lion *) warriors[i];
				if (lion->getCityId() != enemyHQId && lion->getLoyalty() <= 0) {
					showFormatTime(time);
					lion->runAway();
					//Lion逃跑后消失
					delete warriors[i];
					warriors[i] = NULL;
				}
			}
		}
	}
	void showWeapons() {

	}
	void showTotalElements() {
		cout << totalElements << " elements in " << name << " headquarter"
				<< endl;
	}
};

City * initCitys(City * citys, int amount) {
	for (int i = 0; i < amount; i++) {
		citys[i].setId(i + 1);
	}

	return citys;
}

void createElements(City * citys, int amount) {
	for (int i = 0; i < amount; i++) {
		citys[i].createElements();
	}
}

int main() {
	int t; //测试数据的组数
	cin >> t;

	int M, N, K, T;
	int E_dragon, E_ninja, E_iceman, E_lion, E_wolf;
	int F_dragon, F_ninja, F_iceman, F_lion, F_wolf;
	//测试数据有t组
	for (int i = 1; i <= t; i++) {
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

		City *citys = new City[N];
		initCitys(citys, N);
		cout << "citys:" << citys << endl;

		RED_HQ_CITY_ID = 0;
		BLUE_HQ_CITY_ID = N + 1;
		Headquarter redHeadquarter(RED_HQ, M, RED_HQ_CITY_ID, redCategory,
				redElement, redForce);
		Headquarter blueHeadquarter(BLUE_HQ, M, BLUE_HQ_CITY_ID, blueCategory,
				blueElement, blueForce);

		cout << "Case:" << i << endl;
		for (int time = 0; time <= T; time++) {
//			if (debug) {
//				cout << "test time:" << time << endl;
//			}
			switch (time % 60) {
			case 0: //第0分，制造武士
				redHeadquarter.createWarriorsByOrder(time);
				blueHeadquarter.createWarriorsByOrder(time);
				break;
			case 5: //lion逃跑
				redHeadquarter.lionRunAway(time);
				blueHeadquarter.lionRunAway(time);
				break;
			case 10: //武士前进到某一城市/抵达敌军司令部/司令部被占领
				break;
			case 20: //每个城市产出10个生命元
				createElements(citys, N);
				break;
			case 30: //武士取走所在城市的生命元并送给司令部
				break;
			case 35: //武士放箭
				break;
			case 38: //武士使用bomb
				break;
			case 40: //武士主动进攻/反击/战死/欢呼/获取生命元(elements)/旗帜升起
				break;
			case 50: //司令部报告它拥有的生命元数量
				showFormatTime(time);
				redHeadquarter.showTotalElements();
				showFormatTime(time);
				blueHeadquarter.showTotalElements();
				break;
			case 55: //每个武士报告其拥有的武器情况

				break;
			default:
				break;
			}
		}

		delete[] citys;
	}

	return 0;
}

