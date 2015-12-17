/*
 * week6_exercise_wow_final_version.cpp
 *
 *  Created on: 2015年12月16日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
using namespace std;

const bool debug = false;

//司令部
const string RED_HQ = "red", BLUE_HQ = "blue";
int RED_HQ_CITY_ID = 0, BLUE_HQ_CITY_ID = 0;
//武士的种类
const string ICEMAN = "iceman", LION = "lion", WOLF = "wolf", NINJA = "ninja",
		DRAGON = "dragon";
const string Categorys[5] = { DRAGON, NINJA, ICEMAN, LION, WOLF };
int Elements[5], Forces[5];
const int INDEX_DRAGON = 0, INDEX_NINJA = 1, INDEX_ICEMAN = 2, INDEX_LION = 3,
		INDEX_WOLF = 4;
//武器的种类
const string SWORD = "sword", BOMB = "bomb", ARROW = "arrow";
const string WEAPONS[3] = { SWORD, BOMB, ARROW };
int R = 0;
//旗帜
const string RED_FLAG = "red flag";
const string BLUE_FLAG = "blue flag";

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
	virtual ~Weapon() {
	}
	int getNum() {
		return num;
	}
	string getCategory() {
		return category;
	}
	virtual void showInfo()=0;
};

class Sword: public Weapon {
	int force;
public:
	Sword(int force) :
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
	void showInfo() {
		cout << category << '(' << force << ')';
	}
};

class Bomb: public Weapon {
public:
	Bomb() :
			Weapon(1, BOMB) {
	}
	void showInfo() {
		cout << category;
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
	void showInfo() {
		cout << category << '(' << useTimes << ')';
	}
};

Weapon * createWeapon(int num, int ownerForce) {
	Weapon * weapon;
	switch (num % 3) {
	case 0:
		weapon = new Sword(ownerForce / 5);
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
	int enemyHQCityId;
public:
	Warrior(string category, int num, int elements, int force, string hqName,
			int cityId, int enemyHQCityId) :
			category(category), num(num), elements(elements), force(force), hqName(
					hqName), cityId(cityId), enemyHQCityId(enemyHQCityId) {
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
	virtual ~Warrior() {
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
	virtual void march() {
		(hqName == RED_HQ) ? cityId++ : cityId--; //前进到下一城市
		if (cityId == enemyHQCityId) { //是否到达敌方司令部
			cout << hqName << ' ' << category << ' ' << num << " reached "
					<< (hqName == RED_HQ ? "blue" : "red")
					<< " headquarter with ";
		} else {
			cout << hqName << ' ' << category << ' ' << num
					<< " marched to city " << cityId << " with ";
		}
	}
	virtual void showWeapons() {
		cout << hqName << ' ' << category << ' ' << num << " has ";
	}
};

class Dragon: public Warrior {
	Weapon * weapon;
	float morale;
public:
	Dragon(int num, int elements, float morale, int force, string hqName,
			int cityId, int enemyHQCityId) :
			Warrior(DRAGON, num, elements, force, hqName, cityId,
					enemyHQCityId), morale(morale) {
		weapon = createWeapon(num % 3, force);
		cout << "Its morale is " << fixed << setprecision(2) << this->morale
				<< endl;
	}
	~Dragon() {
		if (weapon) {
			delete weapon;
		}
	}
	void march() {
		Warrior::march();
		cout << elements << " elements and force " << force << endl;
	}
	void showWeapons() {
		Warrior::showWeapons();
		if (weapon) {
			weapon->showInfo();
		} else {
			cout << "no weapon";
		}
		cout << endl;
	}
};

class Ninja: public Warrior {
	Weapon * weapons[2];
public:
	Ninja(int num, int elements, int force, string hqName, int cityId,
			int enemyHQCityId) :
			Warrior(NINJA, num, elements, force, hqName, cityId, enemyHQCityId) {
		weapons[0] = createWeapon(num % 3, force);
		weapons[1] = createWeapon((num + 1) % 3, force);
	}
	~Ninja() {
		if (weapons[0]) {
			delete weapons[0];
			weapons[0] = NULL;
		}
		if (weapons[1]) {
			delete weapons[1];
			weapons[1] = NULL;
		}
	}
	void march() {
		Warrior::march();
		cout << elements << " elements and force " << force << endl;
	}
	void showWeapons() {
		Warrior::showWeapons();
		bool flag = false;
		int num = 2;
		while (num >= 0) { //武器的输出顺序为arrow，bomb，sword。对应的编号为2，1，0
			for (int i = 0; i < 2; i++) {
				if (weapons[i] && weapons[i]->getNum() == num) {
					if (flag) {
						cout << ',';
					}
					weapons[i]->showInfo();
					if (!flag) {
						flag = true;
					}
				}
			}
		}
		if (!flag) {
			cout << "no weapon";
		}
		cout << endl;
	}
};

class Iceman: public Warrior {
	Weapon * weapon;
	int marchedSteps = 0;
public:
	Iceman(int num, int elements, int force, string hqName, int cityId,
			int enemyHQCityId) :
			Warrior(ICEMAN, num, elements, force, hqName, cityId, enemyHQCityId) {
		weapon = createWeapon(num % 3, force);
	}
	~Iceman() {
		if (weapon) {
			delete weapon;
		}
	}
	void march() {
		Warrior::march();
		marchedSteps++;
		if (marchedSteps == 2) {
			if (elements <= 9) {
				elements = 1;
			} else {
				elements -= 9;
				force += 20;
			}
			marchedSteps = 0;
		}
		cout << elements << " elements and force " << force << endl;
	}
	void showWeapons() {
		Warrior::showWeapons();
		if (weapon) {
			weapon->showInfo();
		} else {
			cout << "no weapon";
		}
		cout << endl;
	}
};

class Lion: public Warrior {
	int loyalty;
public:
	Lion(int num, int elements, int loyalty, int force, string hqName,
			int cityId, int enemyHQCityId) :
			Warrior(LION, num, elements, force, hqName, cityId, enemyHQCityId) {
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
	void march() {
		Warrior::march();
		cout << elements << " elements and force " << force << endl;
	}
	void showWeapons() { //has no weapon
	}
};

class Wolf: public Warrior {
	Weapon * weapons[3];
public:
	Wolf(int num, int elements, int force, string hqName, int cityId,
			int enemyHQCityId) :
			Warrior(WOLF, num, elements, force, hqName, cityId, enemyHQCityId) {
		for (int i = 0; i < 3; i++) {
			weapons[i] = NULL;
		}
	}
	~Wolf() {
		for (int i = 0; i < 3; i++) {
			if (weapons[i]) {
				delete weapons[i];
				weapons[i] = NULL;
			}
		}
	}
	void march() {
		Warrior::march();
		cout << elements << " elements and force " << force << endl;
	}
	void showWeapons() {
		Warrior::showWeapons();
		bool flag = false;
		int num = 2;
		while (num >= 0) { //武器的输出顺序为arrow，bomb，sword。对应的编号为2，1，0
			for (int i = 0; i < 3; i++) {
				if (weapons[i] && weapons[i]->getNum() == num) {
					if (flag) {
						cout << ',';
					}
					weapons[i]->showInfo();
					if (!flag) {
						flag = true;
					}
				}
			}
		}
		if (!flag) {
			cout << "no weapon";
		}
		cout << endl;
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
	int enemyHQCityId;
	Warrior ** warriors;
//	Warrior * warriors[100];

	int warriorId;
	int index;
	const int *order;
public:
	Headquarter(string name, int totalElements, int cityId, int enemyHQCityId,
			const int *order) :
			name(name), totalElements(totalElements), cityId(cityId), enemyHQCityId(
					enemyHQCityId), order(order) {
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
					totalElements / (element * 1.0f), force, name, cityId,
					enemyHQCityId);
		} else if (category == NINJA) {
			warriors[id - 1] = new Ninja(id, element, force, name, cityId,
					enemyHQCityId);
		} else if (category == ICEMAN) {
			warriors[id - 1] = new Iceman(id, element, force, name, cityId,
					enemyHQCityId);
		} else if (category == LION) {
			warriors[id - 1] = new Lion(id, element, totalElements, force, name,
					cityId, enemyHQCityId);
		} else {
			warriors[id - 1] = new Wolf(id, element, force, name, cityId,
					enemyHQCityId);
		}
		return true;
	}
public:
	bool createWarriorsByOrder(int time) {
		//按顺序制造
		if (createWarrior(time, Categorys[order[index]], warriorId,
				Elements[order[index]], Forces[order[index]])) {
			index = index == 4 ? 0 : index + 1; //从0到4循环
			warriorId++;
			return true;
		}
		return false;
	}
	void lionRunAway(int time) {
		//已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑
//		int enemyHQId = -1;
//		if (name == RED_HQ) {
//			enemyHQId = BLUE_HQ_CITY_ID;
//		} else {
//			enemyHQId = RED_HQ_CITY_ID;
//		}
		for (int i = 0; i < warriorId; i++) {
			if (warriors[i] && warriors[i]->getCategory() == LION) {
				Lion * lion = (Lion *) warriors[i];
				if (lion->getCityId() != enemyHQCityId
						&& lion->getLoyalty() <= 0) {
					showFormatTime(time);
					lion->runAway();
					//Lion逃跑后消失
					delete warriors[i];
					warriors[i] = NULL;
				}
			}
		}
	}
	void warriorsMarch(int time) {
		for (int i = 0; i < warriorId; i++) {
			if (warriors[i]) {
				showFormatTime(time);
				warriors[i]->march();
			}
		}

	}
	void showTotalElements() {
		cout << totalElements << " elements in " << name << " headquarter"
				<< endl;
	}
	void showWeapons(int time) { //按从西向东的顺序
		for (int i = warriorId - 1; i >= 0; i--) {
			if (warriors[i] && warriors[i]->getCategory() != LION) { //lion没有武器
				showFormatTime(time);
				warriors[i]->showWeapons();
			}
		}

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
	//测试数据有t组
	for (int i = 1; i <= t; i++) {
		cin >> M >> N >> R >> K >> T;
		for (int i = 0; i < 5; i++) {
			cin >> Elements[i];
		}
		for (int i = 0; i < 5; i++) {
			cin >> Forces[i];
		}

		City *citys = new City[N];
		initCitys(citys, N);
		cout << "citys:" << citys << endl;

		//红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。
		const int redOrder[5] = { INDEX_ICEMAN, INDEX_LION, INDEX_WOLF,
				INDEX_NINJA, INDEX_DRAGON };

		//蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。
		const int blueOrder[5] = { INDEX_LION, INDEX_DRAGON, INDEX_NINJA,
				INDEX_ICEMAN, INDEX_WOLF };

		RED_HQ_CITY_ID = 0;
		BLUE_HQ_CITY_ID = N + 1;
		Headquarter redHeadquarter(RED_HQ, M, RED_HQ_CITY_ID, BLUE_HQ_CITY_ID,
				redOrder);
		Headquarter blueHeadquarter(BLUE_HQ, M, BLUE_HQ_CITY_ID, RED_HQ_CITY_ID,
				blueOrder);

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
				redHeadquarter.warriorsMarch(time);
				blueHeadquarter.warriorsMarch(time);
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
				redHeadquarter.showWeapons(time);
				blueHeadquarter.showWeapons(time);
				break;
			default:
				break;
			}
		}

		delete[] citys;
	}

	return 0;
}

