#include"stdafx.h"//一定要在开头
#include"screenManager.h"
#include"DisplayObject.h"
#include "scene.h"
#include<algorithm>
#include<cstdlib>
#include<ctime>

void DisplayObject::createdata() {//向缓冲区输出东西的data数组
	data2 = new char* [pictureheigth];
	for (int y = 0; y < pictureheigth; y++)
		data2[y] = new char[picturewidth];

	cleardata();
}

DisplayObject::DisplayObject(int px, int py, int pw, int ph, Bitmap* a) {
	this->walkspeed = 8;
	this->visible = 1;//asdhkajsdkasdka
	this->chilrenifactive = -1;
	this->index = 0;
	this->ifactive = 0;
	this->shineChar = '*';
	this->Displayactive = 0;//Scenemenu中的窗口默认不显示

	this->z = 0;
	this->x = px;
	this->y = py;
	this->pictureheigth = ph;
	this->picturewidth = pw;
	this->resource = new Bitmap();//初始化
	this->resource = a;
	data2 = new char* [pictureheigth];
	for (int y = 0; y < pictureheigth; y++)
		data2[y] = new char[picturewidth];
	for (int y = 0; y < pictureheigth; y++)
		for (int x = 0; x < picturewidth; x++)
			data2[y][x] = ' ';
}

DisplayObject::DisplayObject(int data2w, int data2h) {


	this->walkspeed = 8;
	this->chilrenifactive = -1;
	this->index = 0;
	this->ifactive = 0;
	this->shineChar = '*';
	this->Displayactive = 0;//Scenemenu中的窗口默认不显示
	this->z = 0;
	this->x = 0;
	this->y = 0;
	this->pictureheigth = data2h;
	this->picturewidth = data2w;
	this->visible = 1;
	this->resource = new Bitmap();//初始化


	data2 = new char* [data2h];
	for (int y = 0; y < data2h; y++)
		data2[y] = new char[data2w];
	for (int y = 0; y < data2h; y++)
		for (int x = 0; x < data2w; x++)
			data2[y][x] = ' ';

}
void DisplayObject::cleardata() {//清空数组
	for (int y = 0; y < pictureheigth; y++)
		for (int x = 0; x < picturewidth; x++)
			data2[y][x] = ' ';// 32 + (x + y) % 64;
}
//将第numy行的第numx列的图片传入object对象中，a->height与b->pictureheight相等才能运行
void DisplayObject::writedata2(int numy, int numx) {
	int eachwidth = (this->resource->width / 6);
	int eachheight = (this->resource->height) / 6;
	
	for (int y = eachheight * (numy - 1),i = 0; y < eachheight * (numy - 1) +eachheight;i++,y++)
		for (int x = eachwidth * (numx - 1), j = 0; x < eachwidth * (numx - 1) +eachwidth;j++,x++)
			this->data2[i][j] = this->resource->data1[y][x];
	//a
}
void DisplayObject::backwritedata2(int numy, int numx) {
	int eachwidth = (this->resource->width / 6);
	int eachheight = (this->resource->height) / 6;
	
	for (int y = eachheight * (numy - 1), i = 0; y < eachheight * (numy - 1) + eachheight; i++, y++)
		for (int x = eachwidth * (numx - 1) + eachwidth-1, j = 0; x >= eachwidth * (numx - 1); j++, x--)
			this->data2[i][j] = this->resource->data1[y][x];
}
void DisplayObject::wholewritedata2() {//BItmap的大小得和DisplayObject的pw，ph相等
	for (int y = 0; y < pictureheigth; y++)
		for (int x = 0; x < picturewidth; x++)
			data2[y][x] =this->resource->data1[y][x];
}
void DisplayObject::spritemap(DisplayObject* a) {
	int ax = a->x+a->picturewidth*3, ay = a->y+a->pictureheigth*3;// 
	int ox = ax - SWidth / 2, oy = ay - SHeight* 3 / 4;
	ox = -max(0, min(ox, picturewidth - SWidth));
	oy = -max(0, min(oy, pictureheigth - SHeight));
	x += (ox - x) / 4;
	y += (oy - y) / 4;


}
void DisplayObject::setall() {
	if (this->resource != nullptr) {
	this->pictureheigth = this->resource->height;
	this->picturewidth = this->resource->width;
	this->createdata();
	this->wholewritedata2();
	}
}



vector<vector<char> > DisplayObject::getDisplayData() {
	vector<vector<char> > res;
	for (int i = 0; i < pictureheigth; i++) {
		for (int j = 0; j < picturewidth; j++) {
			res[i][j] = data2[i][j];
		}
	}
	return res;
}
void DisplayObject::render(Scene* scene, int lx, int ly) {
	if (!visible) return;

	for (int i = 0; i < backChildren.size(); i++) {
		DisplayObject* obj = backChildren[i];
		int ox = obj->x; int oy = obj->y;
		obj->render(scene, lx + ox, ly + oy);
	}

	vector<vector<char> > data = getDisplayData();
	for (int y = 0; y < data.size(); y++)
		for (int x = 0; x < data[y].size(); x++) {
			if (data[y][x] != 'T')
				scene->paint(lx + x, ly + y, data[y][x]);
		}
	for (int i = 0; i < children.size(); i++) {
		DisplayObject* obj = children[i];
		int ox = obj->x; int oy = obj->y;
		obj->render(scene, lx + ox, ly + oy);
	}
}
void DisplayObject::render(char** map, int lx, int ly) {

	if (!visible) return;

	for (int i = 0; i < backChildren.size(); i++) {
		DisplayObject* obj = backChildren[i];
		int ox = obj->x; int oy = obj->y;
		obj->render(map, lx + ox, ly + oy);
	}

	
	for (int y = 0; y <this->pictureheigth; y++)//这将不是T的data内容导入map
		for (int x = 0; x <this->picturewidth; x++) {
			if (data2[y][x] != 'T')
			{
				if(ly+y>0&&ly+y<GHeight&&lx+x>0&&lx+x<GWidth)
map[ly + y][lx + x] = data2[y][x];
			}

		}

	for (int i = 0; i < children.size(); i++) {
		DisplayObject* obj = children[i];
		int ox = obj->x; int oy = obj->y;
		obj->render(map, lx + ox, ly + oy);
	}
}
bool DisplayObjectComp(const DisplayObject* a, const DisplayObject* b) {//排序的比较函数，看看谁先渲染
	return (a->z == b->z) ? a->y < b->y : a->z < b->z;
}
//是否shine
char** DisplayObject::getdata2() {
	return this->data2;
}
void DisplayObject::shine(char c, int duration, bool transparent) {
	shineChar = c; shineDuration = duration; shineTransparent = transparent;
}
void DisplayObject::updateShine() {
	if (shineDuration > 0) {
		if (--shineDuration <= 0)
			shineChar = 'T';
	}
}
void DisplayObject::quickRender(char**& map, int lx, int ly,int ifshine) {
	if (ifshine == 1) {
	if (!visible) return;

	// 渲染后面的内容
	for (int i = 0; i < backChildren.size(); i++) {
		DisplayObject* obj = backChildren[i];
		int ox = obj->x; int oy = obj->y;
		obj->quickRender(map, lx + ox, ly + oy);
	}

	// 执行渲染，首先获取Sprite上的Bitmap中的渲染数据（字符数据）
	char** data = this->getdata2();
	int width = this->resource->getWidth();
	int height = this->resource->getHeight();

	// frameRect 为当前Sprite所占的空间矩形
	for (int y = 0; y <10; y++) {//选中其中几行来表示选择
		for (int x = 0; x < this->picturewidth; x++) {
			int dx = x; int dy = y;// +this->y;// +this->x;
			//if (mirror) // 处理镜像
				//dx = frameRect.x + frameRect.width - x;

			int sx = x + lx; int sy = y + ly;
			if(sy >= 0 && sy < GHeight && sx >= 0 && sx < GWidth)
			//if (dy >= 0 && dy < height && dx >= 0 && dx < width &&
				//sy >= 0 && sy < GHeight && sx >= 0 && sx < GWidth)
				// 处理透明情况，T代表透明
				if (data[dy][dx] != 'T') map[sy][sx] =
					(shineDuration > 0 || shineDuration == -1) ? shineChar : data[dy][dx];
				else if ((shineDuration > 0 || shineDuration == -1) && shineTransparent)
					map[sy][sx] = shineChar; // 处理闪烁效果
		}
	}

	// 渲染前面的内容
	for (int i = 0; i < children.size(); i++) {
		DisplayObject* obj = children[i];
		int ox = obj->x; int oy = obj->y;
		obj->quickRender(map, lx + ox, ly + oy);
	}
	}

}
void DisplayObject::quickRender( char**& map,int lx, int ly) {
	//vector<vector<char> > data = getDisplayData()


	if (!visible) return;
	
	for (int i = 0; i < backChildren.size(); i++) {
		DisplayObject* obj = backChildren[i];
		int ox = obj->x; int oy = obj->y;
		obj->render(map, lx + ox, ly + oy);
	}
	
	for (int y = 0; y < this->pictureheigth; y++)//这将不是T的data内容导入map
		for (int x = 0; x <this->picturewidth; x++) {

			if (data2[y][x] != 'T') {
				if (ly + y > 0 && ly + y < GHeight && lx + x>0 && lx + x < GWidth)
map[ly + y][lx + x] = data2[y][x];
			}
				
		}
	
	for (int i = 0; i < children.size(); i++) {

		DisplayObject* obj = children[i];
		int ox = obj->x; int oy = obj->y;
		obj->render(map, lx + ox, ly + oy);
	}
}
void DisplayObject::quickRender(char**& map, int lx, int ly, int numy, int numx) {
	writedata2(numy, numx);
	for (int y = 0; y < pictureheigth; y++)//这将不是T的data内容导入map
		for (int x = 0; x < picturewidth; x++) {
			if (data2[y][x] != 'T')
			{
				//if (ly + y > 0 && ly + y < GHeight && lx + x>0 && lx + x < GWidth)
			map[ly + y][lx + x] = data2[y][x];
			}
		
		}
}
void DisplayObject::writeblood(int width) {

	for (int y = 0; y < pictureheigth; y++) {
for (int x = 0; x < width; x++) {
			data2[y][x] = '*';
		}
for (int x = width; x < this->picturewidth; x++) {
	data2[y][x] = ' ';
}
	}//这将不是T的data内容导入map
		
}
void DisplayObject::setnumber(int num) {//写入number
	int eachw = 9;
	int eachh = 12;
	int temp = 0;
	int weishu = 0;
	int dijige = 1;
	for (int i = 0; i < 10; i++) {
		if (num < pow(10, i)) {
			weishu = i;
			break;
		}
	}

	for (int i = 0; i < weishu; i++) {

		temp = num / pow(10, weishu - i-1);
		for (int y = 0; y < eachh; y++) {
			for (int x = (dijige - 1) * eachw, i = 0; x < (dijige - 1) * eachw + eachw; i++, x++) {
				data2[y][x] =this->resource->data1[y][(temp) * eachw + i];
			}
		}
		num = num - temp * pow(10, weishu - 1-i);
		dijige++;
	}

		for (int y = 0; y < eachh; y++) {//消除剪数字的影响
			for (int x = (weishu) * eachw; x < picturewidth; x++) {
				data2[y][x] = ' ';
			}
		}
	
}
void DisplayObject::ifbehitted(int weax, int weay, int bloodsum, DisplayObject* a) {
	int weaw = 150; int weah = 100;
	for (int i = 0; i < a->children[0]->children.size(); i++) {
		if (a->children[0]->children[i]->isdead == 0) {
		if (a->children[0]->children[i]->x + a->children[0]->children[i]->picturewidth+a->x-60> weax &&
			a->children[0]->children[i]->x + a->children[0]->children[i]->picturewidth+a->x < weax + weaw) {

			if (a->children[0]->children[i]->y + a->children[0]->children[i]->pictureheigth + a->y> weay &&
				a->children[0]->children[i]->y + a->children[0]->children[i]->pictureheigth + a->y < weay + weah)
			{
				a->children[0]->children[i]->blood->writeblood(a->children[0]->children[i]->blood->bloodnum - bloodsum);
			a->children[0]->children[i]->blood->bloodnum -= bloodsum;
			if (a->children[0]->children[i]->blood->bloodnum <= 0) {
				a->children[0]->children[i]->writedata2(6, 4);
				a->children[0]->children[i]->isdead = 1;
				a->children[0]->children[i]->blood->visible = 0;
			}
			}
		}


		

			
			
			/*else if (a->children[i]->y + a->children[i]->pictureheigth <weay + weah &&
				a->children[i]->y + a->children[i]->pictureheigth >weay) {}
				a->children[i]->blood->writeblood(a->children[i]->blood->bloodnum - bloodsum);
				a->children[i]->blood->bloodnum -= bloodsum;*/
			
		}
	}
}

void DisplayObject::updateRandomMove() {
	srand((int)time(0)); 
	for (int i = 0; i < children.size(); i++) {
		DisplayObject* obj = children[i];
		if (obj->isdead == 0) {
obj->tx = obj->x + rand() % 11 - 5;
		obj->ty = obj->y + rand() % 11 - 5;
		//if(obj->ty+obj->pictureheigth<185&& obj->ty + obj->pictureheigth>105)
		obj->moveto(obj->tx, obj->ty);
		}
	}
}
void DisplayObject::setActiveShine() {
	for (int y = 0; y < pictureheigth; y++) {
		for (int x = 0; x < picturewidth; x++)
		{
			if (data2[y][x] == 'T'|| data2[y][x] == ',')//背景为T
				data2[y][x] = ',';
			else {
				data2[y][x] = 'B';
			}
		}
	}
}
void DisplayObject::setback() {

	for (int y = 0; y < pictureheigth; y++) {
		for (int x = 0; x < picturewidth; x++)
		{
			if (data2[y][x] == 'B')
				data2[y][x] = 'B';
			else {
				data2[y][x] = 'T';
			}
		}
	}
}
void DisplayObject::moveto(int x, int y) {
	if (this->ismove)
	{
		int interval = 7;
		static int sum = 0;
		if ( sum<interval) {

			writedata2(2, 1);
			
			sum++;
		}
		else {
			sum++;
			writedata2(2, 3);
			
			if (sum >2*interval) {
				sum = 0;
			}
		}//*******************************
		if (x < this->x) {
			this->x -= 1;
		}
		else if (x > this->x) {
			this->x++;
		}
		else {
			if (y < this->y) {
				this->y -= 1;
			}
			else if (y> this->y) {
				this->y++;
			}
			else
			{
				this->ismove = 0;
			}
		}

	}

}

void DisplayObject::processok(int a) {

	

	switch (a)
	{
	case 1:
	{
		exit(0);
		break;
	}
	case 0:
	{
		Sceneactor* a = new Sceneactor();
		ScreenManager::pushScene(a);
		
		break;
	}
	case 2: {
		exit(0);
		break;
	}
		
	default:
		break;
	}
	
}
void DisplayObject::getmirror(DisplayObject* b) {//当该对象与b相同大小才可
	for (int y = 0,i=0; y < pictureheigth; i++,y++) {
		for (int x = picturewidth - 1,j=0; x >= 0; j++,x--)
		{
			data2[i][j] = b->data2[y][x];
		}
	}

}
void DisplayObject::set_h_and_w() {
	this->pictureheigth = this->resource->height;
	this->picturewidth = this->resource->width;
}


void DisplayObject::addChild(DisplayObject* obj) {
	children.push_back(obj);
	obj->parent = this;
	sort(children.begin(), children.end(), DisplayObjectComp);
}
void DisplayObject::removeChild(DisplayObject* obj) {
	vector<DisplayObject*>::iterator pos;
	pos = find(children.begin(), children.end(), obj);
	if (pos != children.end()) children.erase(pos);
}
void DisplayObject::clearChildren() { children.clear(); }


void DisplayObject::addBackChild(DisplayObject* obj) {
	backChildren.push_back(obj);
	obj->parent = this;
	sort(backChildren.begin(), backChildren.end(), DisplayObjectComp);
}

void DisplayObject::removeBackChild(DisplayObject* obj) {
	vector<DisplayObject*>::iterator pos;
	pos = find(backChildren.begin(), backChildren.end(), obj);
	if (pos != backChildren.end()) backChildren.erase(pos);
}
void DisplayObject::clearBackChildren() { backChildren.clear(); }
void DisplayObject::writeweapon(int numy,int numx)
{
	int eachwidth = (this->resource->width / 3);
	int eachheight = (this->resource->height) / 6;

	for (int y = eachheight * (numy - 1), i = 0; y < eachheight * (numy - 1) + eachheight; i++, y++)
		for (int x = eachwidth * (numx - 1), j = 0; x < eachwidth * (numx - 1) + eachwidth; j++, x++)
			this->data2[i][j] = this->resource->data1[y][x];



}
void DisplayObject::useweapon(DisplayObject* a,int numy,int numx) {//this指向人物，a指向武器
	this->writedata2(2, 3 + numx);
	a->writeweapon(numy, numx);
	
}