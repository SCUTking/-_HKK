#pragma once
#include<vector>
#include"rect.h"
#include"Bitmap.h"
#include"scene.h"
using namespace std;
class Scene;
class Scenestart;
class number;
class DisplayObject{
public:
	int x;
	int y;
	int z;
	int walkspeed;
	bool Displayactive;
	bool visible;
	int chilrenifactive;//专门为Scenemenu准备的
	int ifactive;//1为scenebattle；2为sceneactor；0为scenestart，3为Scenemenu；
	int index;


	//scenebattle
	bool ismove;
	bool isdead;
	int tx;
	int ty;
	void updateRandomMove();
	DisplayObject* blood;
	number* goldGain;
	void setnumber(int num);//金币专有
	int dijiba;//武器专有
	int howmuch;//武器的金额

	int picturewidth;
	int pictureheigth;
	char** data2;
	Bitmap* resource;
	DisplayObject(){
		this->shineChar = '*';
		this->index = 0;
		this->Displayactive = 0;//Scenemenu中的窗口默认不显示
	};
	DisplayObject(int px, int py, int pw, int ph, Bitmap* a);
	DisplayObject(int data2w,int data2h);

	void moveto(int x, int y);
	void quickRender(char**& map, int lx, int ly,int ifshine);
	void setActiveShine();//自己写的，改变data
	void setback();
	void processok(int a);//起始界面的接口函数
	//
	void getmirror(DisplayObject* b);
	void set_h_and_w();

	void setall();

	void addChild(DisplayObject* obj);
	void removeChild(DisplayObject* obj);
	void clearChildren();

	void addBackChild(DisplayObject* obj);
	void removeBackChild(DisplayObject* obj);
	void clearBackChildren();

	void spritemap(DisplayObject* a);
	int bloodnum;
	void writeblood(int width);
	void ifbehitted(int weax, int weay, int bloodsum, DisplayObject* a);
	void writeweapon(int numy, int numx);
	void useweapon(DisplayObject* a, int numy, int numx);
	void wholewritedata2();
	void backwritedata2(int numy, int numx);
	void writedata2(int numy, int numx);//将第numy行的第numx列的图片传入object对象中，a->height与b->pictureheight相等才能运行
	void createdata();//创建object的data
	void cleardata();


	void render(Scene* scene, int lx, int ly);
	void render(char** map, int lx, int ly);
	void quickRender(char**& map, int lx, int ly, int numy, int numx);
	void quickRender(char**& map, int lx, int ly);
	//virtual void updateOthers();
	virtual vector<vector<char> > getDisplayData();
	DisplayObject* parent;
	vector<DisplayObject*> children;
	vector<DisplayObject*> backChildren;
	//int width, height;

	char** getdata2();
	void shine(char c, int duration, bool transparent);
	void updateShine();
	int shineDuration;
	char shineChar;
	bool shineTransparent;
private:
	
};





class actor :public DisplayObject {
public:
	actor(int zbx, int zby, int pw, int ph) {
		this->x = zbx;
		this->y = zbx;
		this->picturewidth = pw;
		this->pictureheigth = ph;
		data2 = new char* [pictureheigth];//当类中有动态成员时应该将动态成员放在构造函数中
		for (int y = 0; y < pictureheigth; y++)
			data2[y] = new char[picturewidth];
		for (int y = 0; y < pictureheigth; y++)
			for (int x = 0; x < picturewidth; x++)
				data2[y][x] = ' ';
	}

};

bool DisplayObjectComp(const DisplayObject* a, const DisplayObject* b); //排序的比较函数，看看谁先渲染


