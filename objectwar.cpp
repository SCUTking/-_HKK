#include"stdafx.h"
#include"objectwar.h"
int WalkSpeed = 4;
Object::Object(int data2w,int data2h,Bitmap* a):DisplayObject(data2w,data2h)
{       
		if (this->resource != nullptr) {
		this->resource = a;
		this->pictureheigth = data2h;
		this->picturewidth = data2w;
		}
		this->x = 100;
		this->y = 100;
this->writedata2(2,1);
this->visible = 1;

//血条
this->blood = new DisplayObject(data2w, 3);
this->blood->writeblood(data2w);
this->addChild(blood);
this->blood->y = -3;
this->blood->bloodnum = data2w;
this->blood->visible = 1;
}
int Object::getLevel() {
	return enemy->level << (difficulty - 1);
}
Enemy* Object::getEnemy() { return enemy; }
void Object::updateRandomMove() {
	
	int tx = x + rand() % 11 - 5;
	int ty = y + rand() % 11 - 5;
	
}
void Object::update() {
	//if (isDead() && !dead) {
		//GameManager::gainGold(getGold());
		dead = true;
	//}
}

objectenemys::objectenemys(){
	this->pictureheigth = 0;
	this->picturewidth = 0;
	//让其不能渲染
}


weapon::weapon(int data2w, int data2h,int dijiba,Bitmap* a):DisplayObject(data2w, data2h) {
	if (this->resource != nullptr) {
		this->resource = a;
		this->pictureheigth = data2h;
		this->picturewidth = data2w;
	}
	this->writeweapon(dijiba, 3);
	this->visible = 0;//默认不显示
}

number::number(int data2w, int data2h, Bitmap* a):DisplayObject(data2w, data2h) {
	if (this->resource != nullptr) {
		this->resource = a;
		this->pictureheigth = data2h;
		this->picturewidth = data2w;
	}

}