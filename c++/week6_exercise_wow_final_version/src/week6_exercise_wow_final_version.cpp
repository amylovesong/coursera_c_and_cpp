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
class Headquarter;
const string RED_HQ = "red", BLUE_HQ = "blue";
int RED_HQ_CITY_ID = 0, BLUE_HQ_CITY_ID = 0;
Headquarter * redHeadquarter, *blueHeadquarter;
//武士
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
//城市
class City;
const int MAX_AMOUNT_CITIES = 20;
City * cities[MAX_AMOUNT_CITIES];

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
	bool isArrow() {
		return category == ARROW;
	}
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
	void use() {
		useTimes--;
	}
	void showInfo() {
		cout << category << '(' << useTimes << ')';
	}
};

class Warrior {
protected:
	string category;
	int num;
	int elements;
	int force;
	string hqName; //武士所属的司令部
	int cityId; //武士当前所处的城市的id，移动时更新
	int enemyHQCityId;
	bool reachedEnemyHQ;
public:
	Warrior(string category, int num, int elements, int force, string hqName,
			int cityId, int enemyHQCityId);
//	Warrior();
	virtual ~Warrior();
	string getCategory();
	string gethqName();
	int getCityId();
	bool hasReachedEnemyHQ();
	virtual bool march();
	void earnElements(int elements);
	virtual void showWeapons();
	virtual bool hasArrow();
	virtual void useArrow();
};

class Headquarter {
	string name;
	int totalElements;
	int cityId;
	int enemyHQCityId;
	Warrior ** warriors;
	int seqReachedEnemyHQ;

	int warriorId;
	int index;
	const int *order;
	bool createWarrior(int time, string category, int id, int element,
			int force);
public:
	Headquarter(string name, int totalElements, int cityId, int enemyHQCityId,
			const int *order);
	~Headquarter();
	bool createWarriorsByOrder(int time);
	void lionRunAway(int time);
	bool warriorsMarch(int time);
	void gainElements(int elements);
	void showTotalElements(int time);
	void showWeapons(int time);
};

class City {
	int id;
	string flag;
	int elements;
	Warrior * redWarrior;
	Warrior * blueWarrior;
public:
	City(int id);
//	City();
	~City();
	void setId(int id);
	int getId();
	void setFlag(string flag);
	string getFlag();
	void createElements();
	int getElements();
	void setRedWarrior(Warrior * red);
	Warrior * getRedWarrior();
	void setBlueWarrior(Warrior * blue);
	Warrior * getBlueWarrior();
};

class Dragon: public Warrior {
	Weapon * weapon;
	float morale;
public:
	Dragon(int num, int elements, float morale, int force, string hqName,
			int cityId, int enemyHQCityId);
	~Dragon();
	bool march();
	void showWeapons();
	bool hasArrow();
	void useArrow();
};

class Ninja: public Warrior {
	Weapon * weapons[2];
public:
	Ninja(int num, int elements, int force, string hqName, int cityId,
			int enemyHQCityId);
	~Ninja();
	bool march();
	void showWeapons();
	bool hasArrow();
};

class Iceman: public Warrior {
	Weapon * weapon;
	int marchedSteps;
public:
	Iceman(int num, int elements, int force, string hqName, int cityId,
			int enemyHQCityId);
	~Iceman();
	bool march();
	void showWeapons();
	bool hasArrow();
};

class Lion: public Warrior {
	int loyalty;
public:
	Lion(int num, int elements, int loyalty, int force, string hqName,
			int cityId, int enemyHQCityId);
	void runAway();
	int getLoyalty();
	bool march();
	void showWeapons();
	bool hasArrow();
};

class Wolf: public Warrior {
	Weapon * weapons[3];
public:
	Wolf(int num, int elements, int force, string hqName, int cityId,
			int enemyHQCityId);
	~Wolf();
	bool march();
	void showWeapons();
	bool hasArrow();
};

void showFormatTime(int time) {
	cout << setfill('0') << setw(3) << time / 60 << ':' << setw(2) << time % 60
			<< ' ';
}

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

void initCitys(int amount) {
	for (int i = 0; i < MAX_AMOUNT_CITIES; i++) {
		if (cities[i]) {
			delete cities[i];
			cities[i] = NULL;
		}
		if (i < amount) {
			cities[i] = new City(i + 1);
		}
	}
}

void warriorsGetElementsFromCity(int time) {
	for (int i = 0; i < MAX_AMOUNT_CITIES; i++) {
		if (cities[i]) {
			Warrior * w = NULL;
			//当前城市只有一个红武士
			if (cities[i]->getRedWarrior() && !cities[i]->getBlueWarrior()) {
				w = cities[i]->getRedWarrior();
			}
			//当前城市只有一个蓝武士
			if (cities[i]->getBlueWarrior() && !cities[i]->getRedWarrior()) {
				w = cities[i]->getBlueWarrior();
			}
			if (w) {
				showFormatTime(time);
				//取得当时城市的所有生命元并传送给司令部
				w->earnElements(cities[i]->getElements());
			}
		}
	}
}

void cityCreateElements(int amount) {
	for (int i = 0; i < amount; i++) {
		(*cities[i]).createElements();
	}
}

void warriorsUseArrow(int amount) {
	for (int c = 0; c < amount; c++) {
		if (cities[c]) {
			City * curCity = cities[c];
			City * nextCity = NULL;
			//当前城市有红武士
			if (curCity->getRedWarrior() && c < amount - 1) {
				nextCity = cities[c + 1];
				if (nextCity->getBlueWarrior()) { //下一个城市有蓝武士
					//放箭

				}
			}
			//当前城市有蓝武士
			if (curCity->getBlueWarrior() && c > 0) {
				nextCity = cities[c - 1];
				if (nextCity->getRedWarrior()) { //下一个城市有红武士
					//放箭

				}
			}
		}
	}
}

City::City(int id) :
		id(id), flag(""), elements(0), redWarrior(NULL), blueWarrior(NULL) {
	if (debug) {
		cout << "test City(int id) id:" << id << endl;
	}
}
//	City() :
//			id(0), flag(""), elements(0), redWarrior(NULL), blueWarrior(NULL) {
//		if (debug) {
//			cout << "test City()" << endl;
//		}
//	}
City::~City() {
	if (debug) {
		cout << "test ~City() id:" << id << endl;
	}
}
void City::setId(int id) {
	this->id = id;
}
int City::getId() {
	return id;
}
void City::setFlag(string flag) {
	this->flag = flag;
}
string City::getFlag() {
	return flag;
}
void City::createElements() {
	elements += 10;
}
int City::getElements() { //生命元被取走
	const int e = elements;
	elements = 0;
	return e;
}
void City::setRedWarrior(Warrior * red) {
	redWarrior = red;
}
Warrior * City::getRedWarrior() {
	return redWarrior;
}
void City::setBlueWarrior(Warrior * blue) {
	blueWarrior = blue;
}
Warrior * City::getBlueWarrior() {
	return blueWarrior;
}

Warrior::Warrior(string category, int num, int elements, int force,
		string hqName, int cityId, int enemyHQCityId) :
		category(category), num(num), elements(elements), force(force), hqName(
				hqName), cityId(cityId), enemyHQCityId(enemyHQCityId), reachedEnemyHQ(
				false) {
	cout << this->category << ' ' << this->num << " born" << endl;
}
//	Warrior() :
//			category(""), num(0), elements(0), force(0), hqName(""), cityId(0) {
//	}
//	void init(string category, int num, int elements, int force, string hqName,
//			int cityId) {
//		this->category = category;
//		this->num = num;
//		this->elements = elements;
//		this->force = force;
//		this->hqName = hqName;
//		this->cityId = cityId;
//	}
Warrior::~Warrior() {
	if (debug) {
		cout << "test ~Warrior() " << hqName << " num:" << num << endl;
	}
}
string Warrior::getCategory() {
	return category;
}
string Warrior::gethqName() {
	return hqName;
}
int Warrior::getCityId() {
	return cityId;
}
bool Warrior::hasReachedEnemyHQ() {
	return reachedEnemyHQ;
}
/**
 * return true if the warrior reached the enemy HQ
 */
bool Warrior::march() {
	if (reachedEnemyHQ) {
		return true;
	}
	(hqName == RED_HQ) ? cityId++ : cityId--; //前进到下一城市
	if (cityId == enemyHQCityId) { //到达敌方司令部
		reachedEnemyHQ = true;
		cout << hqName << ' ' << category << ' ' << num << " reached "
				<< (hqName == RED_HQ ? "blue" : "red") << " headquarter with ";
	} else { //武士在城市中移动
		//更新城市中的武士的指针
		City * curCity = cities[cityId - 1];
		(hqName == RED_HQ) ?
				curCity->setRedWarrior(this) : curCity->setBlueWarrior(this);
		cout << hqName << ' ' << category << ' ' << num << " marched to city "
				<< cityId << " with ";
	}
	return reachedEnemyHQ;
}
void Warrior::earnElements(int elements) {
	(hqName == RED_HQ) ?
			redHeadquarter->gainElements(elements) :
			blueHeadquarter->gainElements(elements);
	cout << hqName << ' ' << category << ' ' << num << " earned " << elements
			<< " elements for his headquarter" << endl;
}
void Warrior::showWeapons() {
	cout << hqName << ' ' << category << ' ' << num << " has ";
}

Dragon::Dragon(int num, int elements, float morale, int force, string hqName,
		int cityId, int enemyHQCityId) :
		Warrior(DRAGON, num, elements, force, hqName, cityId, enemyHQCityId), morale(
				morale) {
	weapon = createWeapon(num % 3, force);
	cout << "Its morale is " << fixed << setprecision(2) << this->morale
			<< endl;
}
Dragon::~Dragon() {
	if (weapon) {
		delete weapon;
	}
}
bool Dragon::march() {
	bool reached = Warrior::march();
	cout << elements << " elements and force " << force << endl;
	return reached;
}
void Dragon::showWeapons() {
	Warrior::showWeapons();
	if (weapon) {
		weapon->showInfo();
	} else {
		cout << "no weapon";
	}
	cout << endl;
}
bool Dragon::hasArrow() {
	return weapon && weapon->isArrow();
}
void Dragon::useArrow() {
	if (hasArrow()) {
		Arrow * arrow = (Arrow *) weapon;
		arrow->use();
		if(!arrow->canUse()){
			delete weapon;
			weapon = NULL;
		}
	}
}

Ninja::Ninja(int num, int elements, int force, string hqName, int cityId,
		int enemyHQCityId) :
		Warrior(NINJA, num, elements, force, hqName, cityId, enemyHQCityId) {
	weapons[0] = createWeapon(num % 3, force);
	weapons[1] = createWeapon((num + 1) % 3, force);
}
Ninja::~Ninja() {
	if (weapons[0]) {
		delete weapons[0];
		weapons[0] = NULL;
	}
	if (weapons[1]) {
		delete weapons[1];
		weapons[1] = NULL;
	}
}
bool Ninja::march() {
	bool reached = Warrior::march();
	cout << elements << " elements and force " << force << endl;
	return reached;
}
void Ninja::showWeapons() {
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

Iceman::Iceman(int num, int elements, int force, string hqName, int cityId,
		int enemyHQCityId) :
		Warrior(ICEMAN, num, elements, force, hqName, cityId, enemyHQCityId), marchedSteps(
				0) {
	weapon = createWeapon(num % 3, force);
}
Iceman::~Iceman() {
	if (weapon) {
		delete weapon;
	}
}
bool Iceman::march() {
	bool reached = Warrior::march();
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
	return reached;
}
void Iceman::showWeapons() {
	Warrior::showWeapons();
	if (weapon) {
		weapon->showInfo();
	} else {
		cout << "no weapon";
	}
	cout << endl;
}

Lion::Lion(int num, int elements, int loyalty, int force, string hqName,
		int cityId, int enemyHQCityId) :
		Warrior(LION, num, elements, force, hqName, cityId, enemyHQCityId) {
	this->loyalty = loyalty;
	cout << "Its loyalty is " << loyalty << endl;
}
void Lion::runAway() {
	cout << hqName << " lion " << num << " ran away" << endl;
}
int Lion::getLoyalty() {
	return loyalty;
}
bool Lion::march() {
	bool reached = Warrior::march();
	cout << elements << " elements and force " << force << endl;
	return reached;
}
void Lion::showWeapons() { //has no weapon
	Warrior::showWeapons();
	cout << "no weapon" << endl;
}

Wolf::Wolf(int num, int elements, int force, string hqName, int cityId,
		int enemyHQCityId) :
		Warrior(WOLF, num, elements, force, hqName, cityId, enemyHQCityId) {
	for (int i = 0; i < 3; i++) {
		weapons[i] = NULL;
	}
}
Wolf::~Wolf() {
	for (int i = 0; i < 3; i++) {
		if (weapons[i]) {
			delete weapons[i];
			weapons[i] = NULL;
		}
	}
}
bool Wolf::march() {
	bool reached = Warrior::march();
	cout << elements << " elements and force " << force << endl;
	return reached;
}
void Wolf::showWeapons() {
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

Headquarter::Headquarter(string name, int totalElements, int cityId,
		int enemyHQCityId, const int *order) :
		name(name), totalElements(totalElements), cityId(cityId), enemyHQCityId(
				enemyHQCityId), seqReachedEnemyHQ(0), warriorId(1), index(0), order(
				order) {
	warriors = new Warrior *[100];
	for (int i = 0; i < 100; i++) {
		warriors[i] = NULL;
	}
}
Headquarter::~Headquarter() {
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
bool Headquarter::createWarrior(int time, string category, int id, int element,
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
bool Headquarter::createWarriorsByOrder(int time) {
	//按顺序制造
	if (createWarrior(time, Categorys[order[index]], warriorId,
			Elements[order[index]], Forces[order[index]])) {
		index = index == 4 ? 0 : index + 1; //从0到4循环
		warriorId++;
		return true;
	}
	return false;
}
void Headquarter::lionRunAway(int time) {
	//已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑
	for (int i = 0; i < warriorId; i++) {
		if (warriors[i] && warriors[i]->getCategory() == LION) {
			Lion * lion = (Lion *) warriors[i];
			if (!lion->hasReachedEnemyHQ() && lion->getLoyalty() <= 0) {
				showFormatTime(time);
				lion->runAway();
				//Lion逃跑后消失
				delete warriors[i];
				warriors[i] = NULL;
			}
		}
	}
}
bool Headquarter::warriorsMarch(int time) {
	for (int i = 0; i < warriorId; i++) {
		if (warriors[i]) {
			if (warriors[i]->hasReachedEnemyHQ()) {
				continue;
			}
			showFormatTime(time);
			if (warriors[i]->march()) { //武士抵达敌军司令部
				seqReachedEnemyHQ++;
			}
			//任何一方的司令部里若是出现了2个敌人，则认为该司令部已被敌人占领
			if (seqReachedEnemyHQ == 2) {
				showFormatTime(time);
				cout << ' ' << ((name == RED_HQ ? BLUE_HQ : RED_HQ))
						<< " headquarter was taken";
				return true;
			}
		}
	}
	return false;
}
void Headquarter::gainElements(int elements) {
	totalElements += elements;
}
void Headquarter::showTotalElements(int time) {
	showFormatTime(time);
	cout << totalElements << " elements in " << name << " headquarter" << endl;
}
void Headquarter::showWeapons(int time) { //按从西向东的顺序
	if (name == RED_HQ) {
		for (int i = warriorId - 1; i >= 0; i--) {
			if (warriors[i]) {
				showFormatTime(time);
				warriors[i]->showWeapons();
			}
		}
	} else if (name == BLUE_HQ) {
		for (int i = 0; i < warriorId; i++) {
			if (warriors[i]) {
				showFormatTime(time);
				warriors[i]->showWeapons();
			}
		}
	}
}

int main() {
	int t; //测试数据的组数
	cin >> t;

	int M, N, K, T;
	bool stop = false;
	//测试数据有t组
	for (int i = 1; i <= t; i++) {
		cin >> M >> N >> R >> K >> T;
		for (int e = 0; e < 5; e++) {
			cin >> Elements[e];
		}
		for (int f = 0; f < 5; f++) {
			cin >> Forces[f];
		}

		initCitys(N);
		cout << "citys:" << cities << endl;

		//红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。
		const int redOrder[5] = { INDEX_ICEMAN, INDEX_LION, INDEX_WOLF,
				INDEX_NINJA, INDEX_DRAGON };

		//蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。
		const int blueOrder[5] = { INDEX_LION, INDEX_DRAGON, INDEX_NINJA,
				INDEX_ICEMAN, INDEX_WOLF };

		RED_HQ_CITY_ID = 0;
		BLUE_HQ_CITY_ID = N + 1;
		redHeadquarter = new Headquarter(RED_HQ, M, RED_HQ_CITY_ID,
				BLUE_HQ_CITY_ID, redOrder);
		blueHeadquarter = new Headquarter(BLUE_HQ, M, BLUE_HQ_CITY_ID,
				RED_HQ_CITY_ID, blueOrder);

		stop = false;
		cout << "Case " << i << ':' << endl;
		for (int time = 0; time <= T; time++) {
//			if (debug) {
//				cout << "test time:" << time << endl;
//			}
			switch (time % 60) {
			case 0: //第0分，制造武士
				redHeadquarter->createWarriorsByOrder(time);
				blueHeadquarter->createWarriorsByOrder(time);
				break;
			case 5: //lion逃跑
				redHeadquarter->lionRunAway(time);
				blueHeadquarter->lionRunAway(time);
				break;
			case 10: //武士前进到某一城市/抵达敌军司令部/司令部被占领
				if (redHeadquarter->warriorsMarch(time)
						|| blueHeadquarter->warriorsMarch(time)) {
					stop = true;
				}
				break;
			case 20: //每个城市产出10个生命元
				cityCreateElements(N);
				break;
			case 30: //武士取走所在城市的生命元并送给司令部
				warriorsGetElementsFromCity(time);
				break;
			case 35: //武士放箭
				warriorsUseArrow(N);
				break;
			case 38: //武士使用bomb
				break;
			case 40: //武士主动进攻/反击/战死/欢呼/获取生命元(elements)/旗帜升起
				break;
			case 50: //司令部报告它拥有的生命元数量
				redHeadquarter->showTotalElements(time);
				blueHeadquarter->showTotalElements(time);
				break;
			case 55: //每个武士报告其拥有的武器情况
				redHeadquarter->showWeapons(time);
				blueHeadquarter->showWeapons(time);
				break;
			}
			if (stop) {
				break;
			}
		}
		delete redHeadquarter;
		redHeadquarter = NULL;
		delete blueHeadquarter;
		blueHeadquarter = NULL;
	}
	//release city instances
	for (int c = 0; c < MAX_AMOUNT_CITIES; c++) {
		if (cities[c]) {
			delete cities[c];
			cities[c] = NULL;
		}
	}

	return 0;
}

