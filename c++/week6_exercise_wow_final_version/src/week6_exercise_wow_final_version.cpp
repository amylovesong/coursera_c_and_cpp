/*
 * week6_exercise_wow_final_version.cpp
 *
 *  Created on: 2015年12月16日
 *      Author: sunxiaoling
 */

#include <iostream>
#include <iomanip>
//#include <math.h>
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
int M, N, R, K, T;
//旗帜
const string RED_FLAG = "red flag";
const string BLUE_FLAG = "blue flag";
//城市
class City;
const int MAX_AMOUNT_CITIES = 20;
City * cities[MAX_AMOUNT_CITIES];

int curTime;

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
	bool isBomb() {
		return category == BOMB;
	}
	bool isSword() {
		return category == SWORD;
	}
};

class Sword: public Weapon {
	int force;
public:
	Sword(int force) :
			Weapon(0, SWORD), force(force) {
	}
	Sword(Sword * sword) :
			Weapon(0, SWORD), force(sword->force) {
	}
	int getForce() {
		return force;
	}
	bool canUse() {
		return force > 0;
	}
	void use() {
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
	Bomb(Bomb * bomb) :
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
	Arrow(Arrow * arrow) :
			Weapon(2, ARROW), R(arrow->R), useTimes(arrow->useTimes) {
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
	int elements; //生命值
	int force; //攻击力
	string hqName; //武士所属的司令部
	int cityId; //武士当前所处的城市的id，移动时更新
	int enemyHQCityId;
	bool reachedEnemyHQ;
public:
	Warrior(string category, int num, int elements, int force, string hqName,
			int cityId, int enemyHQCityId);
	virtual ~Warrior();
	string getCategory();
	int getNum();
	int getElements();
	int getForce();
	string getHQName();
	int getCityId();
	bool hasReachedEnemyHQ();
	virtual bool march();
	void earnElements(int elements);
	virtual void showWeapons();
	virtual bool useArrow()=0; // return true if the warrior has an arrow and use it
	virtual bool useBomb()=0; //return true if the warrior has a bomb and use it
	virtual int getSwordForce()=0; //return the force of sword
	virtual int useSword()=0; // if the warrior has a sword and use it, return the force of sword
	void hitByArrow();
	bool hasDead();
	bool willDead(int damage);
	void showBaseInfo();
	void attack(Warrior * enemy);
	void attackEvent(Warrior * enemy, City * city);
	virtual void fightBack(Warrior * enemy);
	virtual void fightBackEvent(Warrior * enemy, City * city);
	void beKilledEvent(City * city);
	void beAttacked(int damage);
	void addElements(int elements);
	void showElementsAndForceInfo();
	bool isDragon();
	bool isWolf();
	bool isNinja();
	virtual void getVictory(Warrior * enemy, City * city);
	virtual void getFailure(City * city);
	virtual Arrow * getArrow();
	virtual Bomb * getBomb();
	virtual Sword * getSword();
	friend void showMarchInfo(int amount);
};

class Headquarter {
	string name;
	int totalElements;
	int cityId;
	int enemyHQCityId;
	Warrior ** warriors;
	int seqReachedEnemyHQ; //武士到达敌方司令部的序号

	int warriorId;
	int index;
	const int *order;
	bool createWarrior(string category, int id, int element, int force);
	Warrior * enemy[2];
	bool hasShownEnemyInfo[2];
public:
	Headquarter(string name, int totalElements, int cityId, int enemyHQCityId,
			const int *order);
	~Headquarter();
	bool createWarriorsByOrder();
	void lionRunAway();
	bool warriorsMarch();
	void gainElements(int elements);
	void showTotalElements();
	void showWeapons();
	void removeDeadWarrior(int num);
	void awardWarrior(Warrior * warrior);
	void enemyReached(Warrior * enemy);
	friend void showMarchInfo(int amount);
};

class City {
	int id;
	string flag;
	int elements;
	Warrior * redWarrior;
	Warrior * blueWarrior;
	int redWinTimes;
	int blueWinTimes;
	void setFlag(string flag);
public:
	City(int id);
	~City();
	void setId(int id);
	int getId();
	string getFlag();
	void createElements();
	int getElements();
	void setRedWarrior(Warrior * red);
	Warrior * getRedWarrior();
	void setBlueWarrior(Warrior * blue);
	Warrior * getBlueWarrior();
	bool isRedAttack(); //由红武士进攻
	bool isBlueAttack(); //由蓝武士进攻
	void updateWinTimes(Warrior * winner);
	bool isRedWin();
	bool isBlueWin();
	void updateFlag();
};

class Dragon: public Warrior {
	Weapon * weapon;
	double morale;
public:
	Dragon(int num, int elements, double morale, int force, string hqName,
			int cityId, int enemyHQCityId);
	~Dragon();
	void showWeapons();
	bool useArrow();
	bool useBomb();
	int getSwordForce();
	int useSword();
	void getVictory(Warrior * enemy, City * city);
	void getFailure(City * city);
	void yell(City * city);
//	Weapon * getWeapon();
	virtual Arrow * getArrow();
	virtual Bomb * getBomb();
	virtual Sword * getSword();
};

class Ninja: public Warrior {
	Weapon * weapons[2];
public:
	Ninja(int num, int elements, int force, string hqName, int cityId,
			int enemyHQCityId);
	~Ninja();
	void showWeapons();
	bool useArrow();
	bool useBomb();
	int getSwordForce();
	int useSword();
	void fightBack(Warrior * enemy);
	void fightBackEvent(Warrior * enemy, City * city);
//	Weapon ** getWeapons();
	virtual Arrow * getArrow();
	virtual Bomb * getBomb();
	virtual Sword * getSword();
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
	bool useArrow();
	bool useBomb();
	int getSwordForce();
	int useSword();
//	Weapon * getWeapon();
	virtual Arrow * getArrow();
	virtual Bomb * getBomb();
	virtual Sword * getSword();
};

class Lion: public Warrior {
	int loyalty;
public:
	Lion(int num, int elements, int loyalty, int force, string hqName,
			int cityId, int enemyHQCityId);
	void runAway();
	int getLoyalty();
	void showWeapons();
	bool useArrow();
	bool useBomb();
	int getSwordForce();
	int useSword();
	void getFailure(City * city);
};

class Wolf: public Warrior {
	Arrow * arrow;
	Bomb *bomb;
	Sword *sword;
public:
	Wolf(int num, int elements, int force, string hqName, int cityId,
			int enemyHQCityId);
	~Wolf();
	void showWeapons();
	bool useArrow();
	bool useBomb();
	int getSwordForce();
	int useSword();
	void gainWeaponOfEnemy(Warrior * enemy);
	Arrow * getArrow();
	void setArrow(Arrow * newArrow);
	Bomb * getBomb();
	void setBomb(Bomb * newBomb);
	Sword * getSword();
	void setSword(Sword * newSword);
	void setWeapon(Weapon * weapon);
	void getVictory(Warrior * enemy, City * city);
};

void showFormatTime(int time) {
	cout << setfill('0') << setw(3) << time / 60 << ':' << setw(2) << time % 60
			<< ' ';
}
void showCurrentTime() {
	showFormatTime(curTime);
}

Weapon * createWeapon(int num, int ownerForce) {
	Weapon * weapon = NULL;
	switch (num % 3) {
	case 0:
		if (ownerForce / 5 > 0) { //武士降生时得到了一个初始攻击力为0的sword，则视为武士没有sword
			weapon = new Sword(ownerForce / 5);
		}
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

void warriorsGetElementsFromCity() {
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
					if (curCity->getRedWarrior()->useArrow()) {
						nextCity->getBlueWarrior()->hitByArrow();
						showCurrentTime();
						curCity->getRedWarrior()->showBaseInfo();
						cout << " shot";
						if (nextCity->getBlueWarrior()->hasDead()) {
							cout << " and killed ";
							nextCity->getBlueWarrior()->showBaseInfo();
						}
						cout << endl;
					}
				}
			}
			//当前城市有蓝武士
			if (curCity->getBlueWarrior() && c > 0) {
				nextCity = cities[c - 1];
				if (nextCity->getRedWarrior()) { //下一个城市有红武士
					//放箭
					if (curCity->getBlueWarrior()->useArrow()) {
						nextCity->getRedWarrior()->hitByArrow();
						showCurrentTime();
						curCity->getBlueWarrior()->showBaseInfo();
						cout << " shot";
						if (nextCity->getRedWarrior()->hasDead()) {
							cout << " and killed ";
							nextCity->getRedWarrior()->showBaseInfo();
						}
						cout << endl;
					}
				}
			}
		}
	}
	//检查是否有武士被杀死
	for (int c = 0; c < amount; c++) {
		if (cities[c]) {
			Warrior * red = cities[c]->getRedWarrior();
			Warrior * blue = cities[c]->getBlueWarrior();
			if (!red && !blue) {					//没有武士
				continue;
			}
			//由于在第40分钟的时候，有规则“如果敌人在5分钟前已经被飞来的arrow射死，那么仍然视为发生了一场战斗，而且存活者视为获得了战斗的胜利。”
			//所有如果被arrow射死的武士即将发生战斗，则先保留其记录
			if (!blue && (red && red->hasDead())) {			//只有一个武士，且已被射死
				//从司令部的记录中移除已被杀死的武士
				redHeadquarter->removeDeadWarrior(red->getNum());
				//将城市中指向武士的指针置空
				cities[c]->setRedWarrior(NULL);
			}
			if (!red && (blue && blue->hasDead())) {
				blueHeadquarter->removeDeadWarrior(blue->getNum());
				cities[c]->setBlueWarrior(NULL);
			}
			if (blue && blue->hasDead() && red && red->hasDead()) {	//有两个武士，但同时被射死
				redHeadquarter->removeDeadWarrior(red->getNum());
				cities[c]->setRedWarrior(NULL);
				blueHeadquarter->removeDeadWarrior(blue->getNum());
				cities[c]->setBlueWarrior(NULL);
			}
		}
	}
}

void warriorsUseBomb(int amount) {
	bool perishTogether = false;
	for (int c = 0; c < amount; c++) {
		perishTogether = false;
		if (cities[c]) {
			City * curCity = cities[c];
			Warrior * red = curCity->getRedWarrior(), *blue =
					curCity->getBlueWarrior();
			//当前城市中有还活着的两个武士
			if (red && blue && !red->hasDead() && !blue->hasDead()) {
				//该由红武士主动攻击
				if (curCity->isRedAttack()) {
					//蓝武士被攻击
					if (blue->willDead(
							red->getForce() + red->getSwordForce())) {
						perishTogether = blue->useBomb();
						if (perishTogether) {
							showCurrentTime();
							blue->showBaseInfo();
							cout << " used a bomb and killed ";
							red->showBaseInfo();
							cout << endl;
						}
					} else if (!blue->isNinja()
							&& red->willDead(
									blue->getForce() / 2
											+ blue->getSwordForce())) {	//红武士被反击（Ninja不反击）
						perishTogether = red->useBomb();
						if (perishTogether) {
							showCurrentTime();
							red->showBaseInfo();
							cout << " used a bomb and killed ";
							blue->showBaseInfo();
							cout << endl;
						}
					}
				} else if (curCity->isBlueAttack()) {	//该由蓝武士主动攻击
					//红武士被攻击
					if (red->willDead(
							blue->getForce() + blue->getSwordForce())) {
						perishTogether = red->useBomb();
						if (perishTogether) {
							showCurrentTime();
							red->showBaseInfo();
							cout << " used a bomb and killed ";
							blue->showBaseInfo();
							cout << endl;
						}
					} else if (!red->isNinja()
							&& blue->willDead(
									red->getForce() / 2
											+ red->getSwordForce())) {//蓝武士被反击（Ninja不反击）
						perishTogether = blue->useBomb();
						if (perishTogether) {
							showCurrentTime();
							blue->showBaseInfo();
							cout << " used a bomb and killed ";
							red->showBaseInfo();
							cout << endl;
						}
					}
				}
				if (debug) {
					cout << "test perishTogether:" << perishTogether;
				}
				if (perishTogether) {					//同归于尽
					redHeadquarter->removeDeadWarrior(red->getNum());
					blueHeadquarter->removeDeadWarrior(blue->getNum());
					curCity->setRedWarrior(NULL);
					curCity->setBlueWarrior(NULL);
				}
				if (debug) {
					cout << " in city " << curCity->getId() << " red:"
							<< curCity->getRedWarrior() << " blue:"
							<< curCity->getBlueWarrior() << endl;
				}
			}
		}
	}
}

void warriorsBattle(int amount) {
	if (debug) {
		cout << "test warriorsBattle" << endl;
	}
	//战斗前Lion的生命值
	int redLionElements = 0, blueLionElements = 0;
//	Warrior *winner = NULL;
	//由于“如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士”的原则，
	//从西到东发生战斗，如果红武士获胜，则直接获得奖励，并取走城市中的生命元
	//如果蓝武士获胜，先做出标记，再从东向西奖励
	for (int c = 0; c < amount; c++) {
		if (cities[c]) {
			City * curCity = cities[c];
			Warrior * red = curCity->getRedWarrior(), *blue =
					curCity->getBlueWarrior();
			if (red && blue) {
				//reset
				redLionElements = 0, blueLionElements = 0;
//				winner = NULL;
				if (red->hasDead() || blue->hasDead()) {//开始战斗前，如果有一个武士在5分钟前被射死，则存活的武士为胜利者
					if (red->hasDead()) {
//						winner = blue;
						blue->getVictory(red, curCity);
						curCity->updateWinTimes(blue);
					}
					if (blue->hasDead()) {
//						winner = red;
						red->getVictory(blue, curCity);
						curCity->updateWinTimes(red);
					}
				} else {	//两个都还活着，则正常战斗
					//战斗前记录Lion的生命值
					if (red->getCategory() == LION) {
						redLionElements = red->getElements();
					}
					if (blue->getCategory() == LION) {
						blueLionElements = blue->getElements();
					}
					Warrior * activeAttacker = NULL, *beAttckedOne = NULL;
					if (curCity->isRedAttack()) {	//由红武士主动攻击
						activeAttacker = red;
						beAttckedOne = blue;
					} else if (curCity->isBlueAttack()) {	//由蓝武士主动攻击
						activeAttacker = blue;
						beAttckedOne = red;
					}
					if (activeAttacker && beAttckedOne) {
						activeAttacker->attack(beAttckedOne);
						activeAttacker->attackEvent(beAttckedOne, curCity);
						if (beAttckedOne->hasDead()) {	//主动攻击获胜
							beAttckedOne->beKilledEvent(curCity);
							activeAttacker->getVictory(beAttckedOne, curCity);
							curCity->updateWinTimes(activeAttacker);
						} else {
							beAttckedOne->fightBack(activeAttacker);
							beAttckedOne->fightBackEvent(activeAttacker,
									curCity);
							if (activeAttacker->hasDead()) {	//反击获胜
								activeAttacker->beKilledEvent(curCity);
								beAttckedOne->getVictory(activeAttacker,
										curCity);
								curCity->updateWinTimes(beAttckedOne);
							} else {	//平局
								activeAttacker->getFailure(curCity);
								beAttckedOne->getFailure(curCity);
								curCity->updateWinTimes(NULL);
							}
						}
					}
				}
				//武士死亡后消失
				if (red->hasDead()) {
					blueHeadquarter->awardWarrior(blue);
					blue->earnElements(curCity->getElements());
					redHeadquarter->removeDeadWarrior(red->getNum());
					curCity->setRedWarrior(NULL);
					//lion 若是战死，则其战斗前的生命值就会转移到对手身上。所谓“战斗前”，就是每个小时的40分前的一瞬间。
					if (redLionElements > 0) {
						blue->addElements(redLionElements);
					}
				}
				if (blue->hasDead()) {
					redHeadquarter->awardWarrior(red);
					red->earnElements(curCity->getElements());
					blueHeadquarter->removeDeadWarrior(blue->getNum());
					curCity->setBlueWarrior(NULL);
					if (blueLionElements > 0) {
						red->addElements(blueLionElements);
					}
					curCity->updateFlag();
				}
				curCity->updateFlag();
			}
		}
	}
//	//蓝方从东到西奖励武士
//	for (int c = amount - 1; c >= 0; c--) {
//		if (cities[c] && cities[c]->isBlueWin()) {
//			blueHeadquarter->awardWarrior(cities[c]->getBlueWarrior());
//		}
//	}
//	//司令部总是先完成全部奖励工作，然后才开始从各个打了胜仗的城市回收生命元
//	for (int c = 0; c < amount; c++) {
//		if (cities[c]) {
//			City * curCity = cities[c];
//			if (curCity->isBlueWin()) {
//				curCity->getBlueWarrior()->earnElements(curCity->getElements());
//				//升起旗帜
//				curCity->updateFlag();
//			}
//		}
//	}
}

City::City(int id) :
		id(id), flag(""), elements(0), redWarrior(NULL), blueWarrior(NULL), redWinTimes(
				0), blueWinTimes(0) {
	if (debug) {
		cout << "test City(int id) id:" << id << endl;
	}
}
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
	showCurrentTime();
	cout << flag << " raised in city " << id << endl;
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
bool City::isRedAttack() { //插红旗的城市，以及编号为奇数的无旗城市
	return (flag == RED_FLAG) || (flag == "" && id % 2 == 1);
}
bool City::isBlueAttack() { //在插蓝旗的城市，以及编号为偶数的无旗城市
	return (flag == BLUE_FLAG) || (flag == "" && id % 2 == 0);
}
void City::updateWinTimes(Warrior * winner) {
	if (winner) {
		if (winner->getHQName() == RED_HQ) {
			redWinTimes++;
			blueWinTimes = 0;
		} else if (winner->getHQName() == BLUE_HQ) {
			blueWinTimes++;
			redWinTimes = 0;
		}
	} else { //平局
		redWinTimes = 0;
		blueWinTimes = 0;
	}
}
bool City::isRedWin() {
	return redWinTimes > 0;
}
bool City::isBlueWin() {
	return blueWinTimes > 0;
}
void City::updateFlag() {
	if (debug) {
		cout << "test updateFlag in city " << id << " flag:" << flag
				<< " redWinTimes:" << redWinTimes << " blueWinTimes:"
				<< blueWinTimes << endl;
	}
	if (flag != RED_FLAG && redWinTimes >= 2) {
		setFlag(RED_FLAG);
	} else if (flag != BLUE_FLAG && blueWinTimes >= 2) {
		setFlag(BLUE_FLAG);
	}
}

Warrior::Warrior(string category, int num, int elements, int force,
		string hqName, int cityId, int enemyHQCityId) :
		category(category), num(num), elements(elements), force(force), hqName(
				hqName), cityId(cityId), enemyHQCityId(enemyHQCityId), reachedEnemyHQ(
				false) {
	cout << this->category << ' ' << this->num << " born" << endl;
}
Warrior::~Warrior() {
	if (debug) {
		cout << "test ~Warrior() ";
		showBaseInfo();
		cout << endl;
	}
}
string Warrior::getCategory() {
	return category;
}
int Warrior::getNum() {
	return num;
}
int Warrior::getElements() {
	return elements;
}
int Warrior::getForce() {
	return force;
}
string Warrior::getHQName() {
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
	//前进到下一城市之前，先置空当前城市的指针，避免多个城市同时指向同一个武士
	if (cityId > RED_HQ_CITY_ID && cityId < BLUE_HQ_CITY_ID) {
		(hqName == RED_HQ) ?
				cities[cityId - 1]->setRedWarrior(NULL) :
				cities[cityId - 1]->setBlueWarrior(NULL);
	}
	//前进到下一城市
	(hqName == RED_HQ) ? cityId++ : cityId--;
	if (debug) {
		cout << "test march() ";
		showBaseInfo();
		cout << " cityId:" << cityId << endl;

	}
	if (cityId == enemyHQCityId) { //到达敌方司令部
		if (hqName == RED_HQ) {
			blueHeadquarter->enemyReached(this);
		} else if (hqName == BLUE_HQ) {
			redHeadquarter->enemyReached(this);
		}
		reachedEnemyHQ = true;
	} else { //武士在城市中移动，更新城市中的武士的指针
		City * curCity = cities[cityId - 1];
		(hqName == RED_HQ) ?
				curCity->setRedWarrior(this) : curCity->setBlueWarrior(this);
	}
	return reachedEnemyHQ;
}
void Warrior::earnElements(int elements) {
	(hqName == RED_HQ) ?
			redHeadquarter->gainElements(elements) :
			blueHeadquarter->gainElements(elements);
	showCurrentTime();
	showBaseInfo();
	cout << " earned " << elements << " elements for his headquarter" << endl;
}
void Warrior::showWeapons() {
	showCurrentTime();
	showBaseInfo();
	cout << " has ";
}
void Warrior::hitByArrow() {
	elements -= R;
	if (elements < 0) {
		elements = 0;
	}
}
bool Warrior::hasDead() {
	return elements <= 0;
}
bool Warrior::willDead(int damage) {
	if (debug) {
		cout << "test willDead() ";
		showBaseInfo();
		cout << " damage:" << damage << endl;
	}
	return elements <= damage;
}
void Warrior::showBaseInfo() {
	cout << hqName << ' ' << category << ' ' << num;
}
void Warrior::attack(Warrior * enemy) {
	enemy->beAttacked(force);
	enemy->beAttacked(useSword());
}
void Warrior::attackEvent(Warrior * enemy, City * city) {
	showCurrentTime();
	showBaseInfo();
	cout << " attacked ";
	enemy->showBaseInfo();
	cout << " in city " << city->getId() << " with ";
	showElementsAndForceInfo();
}
void Warrior::fightBack(Warrior * enemy) {
	enemy->beAttacked(force / 2);
	enemy->beAttacked(useSword());
}
void Warrior::fightBackEvent(Warrior * enemy, City * city) {
	showCurrentTime();
	showBaseInfo();
	cout << " fought back against ";
	enemy->showBaseInfo();
	cout << " in city " << city->getId() << endl;
}
void Warrior::beKilledEvent(City * city) {
	showCurrentTime();
	showBaseInfo();
	cout << " was killed in city " << city->getId() << endl;
}
void Warrior::beAttacked(int damage) {
	if (debug) {
		cout << "test beAttacked() ";
		showBaseInfo();
		cout << " damage:" << damage;
	}
	elements -= damage;
	if (elements < 0) {		//生命值变为负数时应当做变为0处理
		elements = 0;
	}
	if (debug) {
		cout << " this->elements:" << this->elements << endl;
	}
}
void Warrior::addElements(int elements) {
	if (debug) {
		cout << "test addElements ";
		showBaseInfo();
		cout << " elements:" << elements << " original this->elements:"
				<< this->elements;
	}
	this->elements += elements;
	if (debug) {
		cout << " final this->elements:" << this->elements << endl;
	}
}
void Warrior::showElementsAndForceInfo() {
	cout << elements << " elements and force " << force << endl;
}
bool Warrior::isDragon() {
	return category == DRAGON;
}
bool Warrior::isWolf() {
	return category == WOLF;
}
bool Warrior::isNinja() {
	return category == NINJA;
}
void Warrior::getVictory(Warrior * enemy, City * city) {

}
void Warrior::getFailure(City * city) {

}
Arrow * Warrior::getArrow() {
	return NULL;
}
Bomb * Warrior::getBomb() {
	return NULL;
}
Sword * Warrior::getSword() {
	return NULL;
}

Dragon::Dragon(int num, int elements, double morale, int force, string hqName,
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
void Dragon::showWeapons() {
	Warrior::showWeapons();
	if (weapon) {
		weapon->showInfo();
	} else {
		cout << "no weapon";
	}
	cout << endl;
}
bool Dragon::useArrow() {
	if (weapon && weapon->isArrow()) {
		Arrow * arrow = (Arrow *) weapon;
		arrow->use();
		if (!arrow->canUse()) {
			delete weapon;
			weapon = NULL;
		}
		return true;
	}
	return false;
}
bool Dragon::useBomb() {
	if (weapon && weapon->isBomb()) {
		delete weapon;
		weapon = NULL;
		return true;
	}
	return false;
}
int Dragon::getSwordForce() {
	if (weapon && weapon->isSword()) {
		return ((Sword *) weapon)->getForce();
	}
	return 0;
}
int Dragon::useSword() {
	if (weapon && weapon->isSword()) {
		Sword * sword = (Sword *) weapon;
		int force = sword->getForce();
		sword->use();
		if (!sword->canUse()) {
			delete weapon;
			weapon = NULL;
		}
		return force;
	}
	return 0;
}
void Dragon::getVictory(Warrior * enemy, City * city) {
	morale += 0.2;
	if (hqName == RED_HQ && city->isRedAttack()) {
		yell(city);
	} else if (hqName == BLUE_HQ && city->isBlueAttack()) {
		yell(city);
	}
}
void Dragon::getFailure(City * city) {
	morale -= 0.2;
	if (hqName == RED_HQ && city->isRedAttack()) {
		yell(city);
	} else if (hqName == BLUE_HQ && city->isBlueAttack()) {
		yell(city);
	}
}
void Dragon::yell(City * city) {
	if (morale > 0.8) {
		showCurrentTime();
		showBaseInfo();
		cout << " yelled in city " << city->getId() << endl;
	}
}
//Weapon * Dragon::getWeapon() {
//	return weapon;
//}
Arrow * Dragon::getArrow() {
	return (weapon && weapon->isArrow()) ? (Arrow *) weapon : NULL;
}
Bomb * Dragon::getBomb() {
	return (weapon && weapon->isBomb()) ? (Bomb *) weapon : NULL;
}
Sword * Dragon::getSword() {
	return (weapon && weapon->isSword()) ? (Sword *) weapon : NULL;
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
		num--;
	}
	if (!flag) {
		cout << "no weapon";
	}
	cout << endl;
}
bool Ninja::useArrow() {
	int arrowIndex = -1;
	for (int w = 0; w < 2; w++) {
		if (weapons[w] && weapons[w]->isArrow()) {
			arrowIndex = w;
		}
	}
	if (arrowIndex >= 0) {
		Arrow * arrow = (Arrow *) weapons[arrowIndex];
		arrow->use();
		if (!arrow->canUse()) {
			delete arrow;
			weapons[arrowIndex] = NULL;
		}
		return true;
	}
	return false;
}
bool Ninja::useBomb() {
	int bombIndex = -1;
	for (int w = 0; w < 2; w++) {
		if (weapons[w] && weapons[w]->isBomb()) {
			bombIndex = w;
		}
	}
	if (bombIndex >= 0) {
		delete weapons[bombIndex];
		weapons[bombIndex] = NULL;
		return true;
	}
	return false;
}
int Ninja::getSwordForce() {
	for (int w = 0; w < 2; w++) {
		if (weapons[w] && weapons[w]->isSword()) {
			return ((Sword *) weapons[w])->getForce();
		}
	}
	return 0;
}
int Ninja::useSword() {
	for (int w = 0; w < 2; w++) {
		if (weapons[w] && weapons[w]->isSword()) {
			Sword * sword = (Sword *) weapons[w];
			int force = sword->getForce();
			sword->use();
			if (!sword->canUse()) {
				delete weapons[w];
				weapons[w] = NULL;
			}
			return force;
		}
	}
	return 0;
}
void Ninja::fightBack(Warrior * enemy) {

}
void Ninja::fightBackEvent(Warrior * enemy, City * city) { //ninja 挨打了也从不反击敌人。

}
//Weapon ** Ninja::getWeapons() {
//	return weapons;
//}
Arrow * Ninja::getArrow() {
	for (int i = 0; i < 2; i++) {
		if (weapons[i] && weapons[i]->isArrow()) {
			return (Arrow *) weapons[i];
		}
	}
	return NULL;
}
Bomb * Ninja::getBomb() {
	for (int i = 0; i < 2; i++) {
		if (weapons[i] && weapons[i]->isBomb()) {
			return (Bomb *) weapons[i];
		}
	}
	return NULL;
}
Sword * Ninja::getSword() {
	for (int i = 0; i < 2; i++) {
		if (weapons[i] && weapons[i]->isSword()) {
			return (Sword *) weapons[i];
		}
	}
	return NULL;
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
		}
		force += 20;
		marchedSteps = 0;
	}
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
bool Iceman::useArrow() {
	if (weapon && weapon->isArrow()) {
		Arrow * arrow = (Arrow *) weapon;
		arrow->use();
		if (!arrow->canUse()) {
			delete weapon;
			weapon = NULL;
		}
		return true;
	}
	return false;
}
bool Iceman::useBomb() {
	if (weapon && weapon->isBomb()) {
		delete weapon;
		weapon = NULL;
		return true;
	}
	return false;
}
int Iceman::getSwordForce() {
	if (weapon && weapon->isSword()) {
		return ((Sword *) weapon)->getForce();
	}
	return 0;
}
int Iceman::useSword() {
	if (weapon && weapon->isSword()) {
		Sword * sword = (Sword *) weapon;
		int force = sword->getForce();
		sword->use();
		if (!sword->canUse()) {
			delete weapon;
			weapon = NULL;
		}
		return force;
	}
	return 0;
}
//Weapon * Iceman::getWeapon() {
//	return weapon;
//}
Arrow * Iceman::getArrow() {
	return (weapon && weapon->isArrow()) ? (Arrow *) weapon : NULL;
}
Bomb * Iceman::getBomb() {
	return (weapon && weapon->isBomb()) ? (Bomb *) weapon : NULL;
}
Sword * Iceman::getSword() {
	return (weapon && weapon->isSword()) ? (Sword *) weapon : NULL;
}

Lion::Lion(int num, int elements, int loyalty, int force, string hqName,
		int cityId, int enemyHQCityId) :
		Warrior(LION, num, elements, force, hqName, cityId, enemyHQCityId) {
	this->loyalty = loyalty;
	cout << "Its loyalty is " << loyalty << endl;
}
void Lion::runAway() {
	showBaseInfo();
	cout << " ran away" << endl;
}
int Lion::getLoyalty() {
	return loyalty;
}
void Lion::showWeapons() { //has no weapon
	Warrior::showWeapons();
	cout << "no weapon" << endl;
}
bool Lion::useArrow() {
	return false;
}
bool Lion::useBomb() {
	return false;
}
int Lion::getSwordForce() {
	return 0;
}
int Lion::useSword() {
	return 0;
}
void Lion::getFailure(City * city) {
	loyalty -= K;
}

Wolf::Wolf(int num, int elements, int force, string hqName, int cityId,
		int enemyHQCityId) :
		Warrior(WOLF, num, elements, force, hqName, cityId, enemyHQCityId), arrow(
		NULL), bomb(NULL), sword(NULL) {
}
Wolf::~Wolf() {
	if (arrow) {
		delete arrow;
	}
	if (bomb) {
		delete bomb;
	}
	if (sword) {
		delete sword;
	}
}
void Wolf::showWeapons() {
	Warrior::showWeapons();
	//武器的输出顺序为arrow，bomb，sword。对应的编号为2，1，0
	bool flag = false;
	if (arrow) {
		arrow->showInfo();
		flag = true;
	}
	if (bomb) {
		if (flag) {
			cout << ',';
		}
		bomb->showInfo();
		flag = true;
	}
	if (sword) {
		if (flag) {
			cout << ',';
		}
		sword->showInfo();
		flag = true;
	}
	if (!flag) {
		cout << "no weapon";
	}
	cout << endl;
}
bool Wolf::useArrow() {
	if (arrow) {
		arrow->use();
		if (!arrow->canUse()) {
			delete arrow;
			arrow = NULL;
		}
		return true;
	}
	return false;
}
bool Wolf::useBomb() {
	if (bomb) {
		delete bomb;
		bomb = NULL;
		return true;
	}
	return false;
}
int Wolf::getSwordForce() {
	if (sword) {
		return sword->getForce();
	}
	return 0;
}
int Wolf::useSword() {
	if (sword) {
		int force = sword->getForce();
		sword->use();
		if (!sword->canUse()) {
			delete sword;
			sword = NULL;
		}
		return force;
	}
	return 0;
}
void Wolf::gainWeaponOfEnemy(Warrior * enemy) {
	setArrow(enemy->getArrow());
	setBomb(enemy->getBomb());
	setSword(enemy->getSword());
//	if (enemy->getCategory() == DRAGON) {
//		Weapon * weapon = ((Dragon *) enemy)->getWeapon();
//		setWeapon(weapon);
//	} else if (enemy->getCategory() == ICEMAN) {
//		Weapon * weapon = ((Iceman *) enemy)->getWeapon();
//		setWeapon(weapon);
//	} else if (enemy->getCategory() == NINJA) {
//		Weapon ** weapons = ((Ninja *) enemy)->getWeapons();
//		setWeapon(weapons[0]);
//		setWeapon(weapons[1]);
//	} else if (enemy->getCategory() == WOLF) {
//		Wolf * wolf = (Wolf *) enemy;
//		setArrow(wolf->getArrow());
//		setBomb(wolf->getBomb());
//		setSword(wolf->getSword());
//	}
}
void Wolf::setWeapon(Weapon * weapon) {
	if (weapon) {
		if (weapon->isArrow()) {
			setArrow((Arrow *) weapon);
		} else if (weapon->isBomb()) {
			setBomb((Bomb *) weapon);
		} else if (weapon->isSword()) {
			setSword((Sword *) weapon);
		}
	}
}
void Wolf::getVictory(Warrior * enemy, City * city) {
	gainWeaponOfEnemy(enemy);
}
Arrow * Wolf::getArrow() {
	return arrow;
}
void Wolf::setArrow(Arrow * newArrow) {
	if (!arrow && newArrow) {
		arrow = new Arrow(newArrow);
	}
}
Bomb * Wolf::getBomb() {
	return bomb;
}
void Wolf::setBomb(Bomb * newBomb) {
	if (!bomb && newBomb) {
		bomb = new Bomb(newBomb);
	}
}
Sword * Wolf::getSword() {
	return sword;
}
void Wolf::setSword(Sword * newSword) {
	if (!sword && newSword) {
		sword = new Sword(newSword);
	}
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
	for (int i = 0; i < 2; i++) {
		enemy[i] = NULL;
		hasShownEnemyInfo[i] = false;
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
bool Headquarter::createWarrior(string category, int id, int element,
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
	showCurrentTime();
	cout << name << " ";
	totalElements -= element;
	if (category == DRAGON) {
		warriors[id - 1] = new Dragon(id, element,
				totalElements / (element * 1.0), force, name, cityId,
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
	if (debug) {
		cout << "test the warrior created is ";
		warriors[id - 1]->showBaseInfo();
		cout << endl;
	}
	return true;
}
bool Headquarter::createWarriorsByOrder() {
	//按顺序制造
	if (createWarrior(Categorys[order[index]], warriorId,
			Elements[order[index]], Forces[order[index]])) {
		index = index == 4 ? 0 : index + 1; //从0到4循环
		warriorId++;
		return true;
	}
	return false;
}
void Headquarter::lionRunAway() {
	//已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑
	for (int i = 0; i < warriorId; i++) {
		if (warriors[i] && warriors[i]->getCategory() == LION) {
			Lion * lion = (Lion *) warriors[i];
			if (!lion->hasReachedEnemyHQ() && lion->getLoyalty() <= 0) {
				showCurrentTime();
				lion->runAway();
				//Lion逃跑后消失
				//置空所在城市的指针
				int cityId = lion->getCityId();
				if (debug) {
					cout << "test lionRunAway cityId:" << cityId << endl;
				}
				if (cityId > RED_HQ_CITY_ID && cityId < BLUE_HQ_CITY_ID) {
					(lion->getHQName() == RED_HQ) ?
							cities[cityId - 1]->setRedWarrior(NULL) :
							cities[cityId - 1]->setBlueWarrior(NULL);
				}
				delete warriors[i];
				warriors[i] = NULL;
			}
		}
	}
}
bool Headquarter::warriorsMarch() {
	if (debug) {
		cout << "test " << name << " warriorsMarch warriorId:" << warriorId
				<< endl;
	}
	bool reached = false;
	for (int i = 0; i < warriorId; i++) {
		if (debug) {
			cout << "warriors[" << i << "] is " << warriors[i];
			if (warriors[i]) {
				cout << ' ';
				warriors[i]->showBaseInfo();
			}
			cout << endl;
		}
		if (warriors[i]) {
			if (debug) {
				warriors[i]->showBaseInfo();
				cout << " hasReachedEnemyHQ:"
						<< warriors[i]->hasReachedEnemyHQ() << endl;
			}
			if (warriors[i]->hasReachedEnemyHQ()) {
				continue;
			}
			if (warriors[i]->march()) { //武士抵达敌军司令部
				seqReachedEnemyHQ++;
			}
			//任何一方的司令部里若是出现了2个敌人，则认为该司令部已被敌人占领
			if (seqReachedEnemyHQ >= 2) {
				reached = true;
			}
		}
	}
	return reached;
}
void showMarchInfo(int amount) { //从西向东
	if (debug) {
		cout << "test showMarchInfo" << endl;
	}
	//首先是红魔司令部
	for (int i = 0; i < 2; i++) {
		if (redHeadquarter->enemy[i] && !redHeadquarter->hasShownEnemyInfo[i]) {
			redHeadquarter->hasShownEnemyInfo[i] = true;
			showCurrentTime();
			redHeadquarter->enemy[i]->showBaseInfo();
			cout << " reached " << RED_HQ << " headquarter with ";
			redHeadquarter->enemy[i]->showElementsAndForceInfo();
		}
	}
	//任何一方的司令部里若是出现了2个敌人，则认为该司令部已被敌人占领
	if (blueHeadquarter->seqReachedEnemyHQ >= 2) {
		showCurrentTime();
		cout << RED_HQ << " headquarter was taken" << endl;
	}
	//中间的N个城市
	for (int c = 0; c < amount; c++) {
		if (cities[c]) {
			City * curCity = cities[c];
			Warrior * red = curCity->getRedWarrior();
			Warrior * blue = curCity->getBlueWarrior();
			//武士在城市中移动
			if (red) {
				showCurrentTime();
				red->showBaseInfo();
				cout << " marched to city " << curCity->getId() << " with ";
				red->showElementsAndForceInfo();
			}
			if (blue) {
				showCurrentTime();
				blue->showBaseInfo();
				cout << " marched to city " << curCity->getId() << " with ";
				blue->showElementsAndForceInfo();
			}
		}
	}
	//最后是蓝魔司令部
	for (int i = 0; i < 2; i++) {
		if (debug) {
			cout << " blueHeadquarter enemy[" << i << "]:"
					<< blueHeadquarter->enemy[i] << " hasShownEnemyInfo:"
					<< blueHeadquarter->hasShownEnemyInfo[i] << endl;
		}
		if (blueHeadquarter->enemy[i]
				&& !blueHeadquarter->hasShownEnemyInfo[i]) {
			blueHeadquarter->hasShownEnemyInfo[i] = true;
			showCurrentTime();
			blueHeadquarter->enemy[i]->showBaseInfo();
			cout << " reached " << BLUE_HQ << " headquarter with ";
			blueHeadquarter->enemy[i]->showElementsAndForceInfo();
		}
	}
	if (redHeadquarter->seqReachedEnemyHQ >= 2) {
		showCurrentTime();
		cout << BLUE_HQ << " headquarter was taken" << endl;
	}
}
void Headquarter::gainElements(int elements) {
	totalElements += elements;
}
void Headquarter::showTotalElements() {
	showCurrentTime();
	cout << totalElements << " elements in " << name << " headquarter" << endl;
}
void Headquarter::showWeapons() { //按从西向东的顺序
	if (name == RED_HQ) {
		for (int i = warriorId - 1; i >= 0; i--) {
			if (warriors[i]) {
				warriors[i]->showWeapons();
			}
		}
	} else if (name == BLUE_HQ) {
		for (int i = 0; i < warriorId; i++) {
			if (warriors[i]) {
				warriors[i]->showWeapons();
			}
		}
	}
}
void Headquarter::removeDeadWarrior(int num) {
	if (warriors[num - 1]) {
		delete warriors[num - 1];
		warriors[num - 1] = NULL;
	}
}
void Headquarter::awardWarrior(Warrior * warrior) {
	if (totalElements >= 8) {
		warrior->addElements(8);
		totalElements -= 8;
	}
}
void Headquarter::enemyReached(Warrior * enemy) {
	if (debug) {
		cout << "test " << name << " enemyReached() enemy:";
		enemy->showBaseInfo();
		cout << endl;
	}
	for (int i = 0; i < 2; i++) {
		if (!this->enemy[i]) {
			this->enemy[i] = enemy;
			break;
		}
	}
}

int main() {
	int t; //测试数据的组数
	cin >> t;
	bool stop = false, redReached = false, blueReached = false;
	for (int i = 1; i <= t; i++) {
		cin >> M >> N >> R >> K >> T;
		for (int e = 0; e < 5; e++) {
			cin >> Elements[e];
		}
		for (int f = 0; f < 5; f++) {
			cin >> Forces[f];
		}
		initCitys(N);
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
		redReached = false;
		blueReached = false;
		cout << "Case " << i << ':' << endl;
		for (curTime = 0; curTime <= T; curTime++) {
			if (debug) {
				cout << "test curTime:" << curTime << endl;
			}
			switch (curTime % 60) {
			case 0: //第0分，制造武士
				redHeadquarter->createWarriorsByOrder();
				blueHeadquarter->createWarriorsByOrder();
				break;
			case 5: //lion逃跑
				redHeadquarter->lionRunAway();
				blueHeadquarter->lionRunAway();
				break;
			case 10: //武士前进到某一城市/抵达敌军司令部/司令部被占领
				redReached = redHeadquarter->warriorsMarch();
				blueReached = blueHeadquarter->warriorsMarch();
				showMarchInfo(N);
				stop = redReached || blueReached;
				break;
			case 20: //每个城市产出10个生命元
				cityCreateElements(N);
				break;
			case 30: //武士取走所在城市的生命元并送给司令部
				warriorsGetElementsFromCity();
				break;
			case 35: //武士放箭
				warriorsUseArrow(N);
				break;
			case 38: //武士使用bomb
				warriorsUseBomb(N);
				break;
			case 40: //武士主动进攻/反击/战死/欢呼/获取生命元(elements)/旗帜升起
				warriorsBattle(N);
				break;
			case 50: //司令部报告它拥有的生命元数量
				redHeadquarter->showTotalElements();
				blueHeadquarter->showTotalElements();
				break;
			case 55: //每个武士报告其拥有的武器情况
				redHeadquarter->showWeapons();
				blueHeadquarter->showWeapons();
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

