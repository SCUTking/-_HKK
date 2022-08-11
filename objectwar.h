#pragma once
#include"Database.h"
#include"DisplayObject.h"
class Object: public DisplayObject {
public:
	static const int EnemyAttackDelay;
	static const int WalkSpeed;
	Object();
	Object(int id, int difficulty = 1);
	Object(Enemy* enemy, int difficulty = 1);
	Object(int data2w, int data2h, Bitmap* a);

	void update();

	//int baseParam(int id);
	int getLevel();
	int getGold();


	Enemy* getEnemy();
	void updateRandomMove();
private:
	vector<int> skillRate;
	int sumRate;
	int difficulty;
	Enemy* enemy;

protected:
	void updateMove();

	bool dead = false;
};
class objectenemys:public DisplayObject{//敌人的集合
public:
	objectenemys();
};



class weapon :public DisplayObject {
public:
	weapon(int data2w, int data2h,int dijiba,Bitmap* a);
};

class number :public DisplayObject {
public:
	number(int data2w, int data2h, Bitmap* a);
};