#include"stdafx.h"
#include"key.h"
#include<conio.h>
#include"DisplayObject.h"
char keyboard_actor(DisplayObject* obj)
{
	static int sum = 0;
	if (sum < 5) {
		sum++;
	}
	else
	{
	//隐藏刀
	obj->children[0]->visible = 0;
	//还原角色
	obj->writedata2(2, 1);
	sum = 0;
	}

	int uplineY = 105; int downlineY = 185; int walkspeed = 8;
	char ch;
	if (_kbhit()) {
		ch = _getch();//不用在控制台输出
		//getchar() 函数在读入一个字符时 必须按一下 enter 键，该代码才会继续运行;
		//但是 getch() 函数读入一个字符时 不用 enter 代码会继续跑
		if (ch == 119 || ch == 115 || ch == 100 || ch == 97||ch=='j'||ch=='k') {
			if (ch == 119) {//w 向上
				if (obj->y+obj->pictureheigth-walkspeed>=uplineY)
				{
				obj->y -= 8;
				return 'w';
				}
				
			}
			else if (ch == 115) {//s 向下
				if (obj->y + obj->pictureheigth +walkspeed <= downlineY) {
				obj->y += 8;
				return 's';
				}

			}
			else if (ch == 100) {//d 向右
				if (obj->x < 800-8) {
				obj->x += 8;
				return 'd';
				}

			}
			else if (ch == 97) {//a 向左
				if (obj->x >= 8) {
					obj->x -= 8;
					return 'a';
				}

			}
			else if (ch == 'j') {
				obj->writedata2(2, 4);
				obj->children[0]->visible = 1;
				obj->children[0]->writeweapon(obj->dijiba, 2);
				return 'j';
			}
			else if (ch == 'k') {
				return 'k';
			}

		}
	}
	else {//没有键盘的输入函数返回 fffffff
		return 'f';
	}
}


int keyboard_select_Scenestart(DisplayObject* a) {

	char ch;
	if (_kbhit) {
		ch = _getch();//不用在控制台输出
		//getchar() 函数在读入一个字符时 必须按一下 enter 键，该代码才会继续运行;
		//但是 getch() 函数读入一个字符时 不用 enter 代码会继续跑
		if (ch == 119 || ch == 115 ) {
			if (ch == 115) {//w 向上
				
	a->children[a->index]->setback();
				if (a->index == 0) {
					a->index = 2;
					a->children[a->index]->setActiveShine();
				}
				else {
					a->index--;
					a->children[a->index]->setActiveShine();
				}
			//***************************************************************w和s反了才能成功
			}
			else if (ch == 119) {//s 向下
				
					a->children[a->index]->setback();
				
				if (a->index == 2) {

					a->index = 0;
					a->children[a->index]->setActiveShine();
				}
				else {
					a->index++;
					a->children[a->index]->setActiveShine();
				}
			}
		}
		if (ch == '\r') {
			return a->index;//按下enter健
		}
		
	}
}

int keyboard_select_SceneMenu(DisplayObject* a) {

	static int work6 = 0;
	if (work6 == 0) {
		a->index = 0;
		work6 = 1;
		return -1;
	}
	char ch;
	if (_kbhit) {
		ch = _getch();//不用在控制台输出
		//getchar() 函数在读入一个字符时 必须按一下 enter 键，该代码才会继续运行;
		//但是 getch() 函数读入一个字符时 不用 enter 代码会继续跑
		if (ch == 119 || ch == 115) {
			if (ch == 119) {//w 向上

				a->children[a->index]->setback();


				if (a->index == 0) {
					
					a->index =5;
					a->children[a->index]->setActiveShine();
				}
				else {

					a->index--;
					a->children[a->index]->setActiveShine();
				}

			}
			else if (ch == 115) {//s 向下

				a->children[a->index]->setback();

				if (a->index == 5) {

					a->index = 0;
					a->children[a->index]->setActiveShine();
				}
				else {

					a->index++;
					a->children[a->index]->setActiveShine();
				}
				
			}
			return -1;
		}

		else if (ch == '\r') {
			return a->index;//按下enter健
		}
		else{
			//work6 = 0;
			return -1;
		}

	}
}
int keyboard_select_SceneMenu_mapwindow(DisplayObject* a)
{
	static int work7 = 0;
	if (work7== 0) {
		a->index = 0;//mapwindow的第一个地图
		work7 = 1;
		return a->index;
	}
	char ch;
	if (_kbhit()) {
		ch = _getch();//不用在控制台输出
		//getchar() 函数在读入一个字符时 必须按一下 enter 键，该代码才会继续运行;
		//但是 getch() 函数读入一个字符时 不用 enter 代码会继续跑
		if (ch == 119 || ch == 115 || ch == 100 || ch == 97) {
			if (ch == 119) {//w 向上
				if (a->index == 2) {
					a->index = 0;
				}
				else if(a->index == 0) {
					a->index = 2;
				}
				else if (a->index == 1) {
					a->index = 3;
				}
				else if (a->index == 3) {
					a->index = 1;
				}

			}
			else if (ch == 115) {//s 向下

				if (a->index == 2) {
					a->index = 0;
				}
				else if (a->index == 0) {
					a->index = 2;
				}
				else if (a->index == 1) {
					a->index = 3;
				}
				else if (a->index == 3) {
					a->index = 1;
				}
			}
			else if (ch == 100) {//d
				if (a->index == 2) {
					a->index = 3;
				}
				else if (a->index == 3) {
					a->index = 2;
				}
				else if (a->index == 0) {
					a->index = 1;
				}
				else if (a->index == 1) {
					a->index = 0;
				}
			}
			else if (ch == 97) {//a

				if (a->index == 2) {
					a->index = 3;
				}
				else if (a->index == 3) {
					a->index = 2;
				}
				else if (a->index == 0) {
					a->index = 1;
				}
				else if (a->index == 1) {
					a->index = 0;
				}
			}
			return a->index;
		}
		if (ch == '\r') {
			return a->index+4;//按下enter健 加一点后见一点
		}
	}
		return -1;
}

int keyboard_select_SceneMenu_maplevelwindow(DisplayObject* a) {
	static int work17 = 0;
	if (work17 == 0) {
		a->children[a->index]->setActiveShine();//重置
		a->children[a->index]->setback();//重置
		a->index = 0;//重置index否者会越外界
		a->children[a->index]->setActiveShine();
		work17 = 1;
		
	}
	char ch;
	if (_kbhit()) {//阻塞
		ch = _getch();//不用在控制台输出
		//getchar() 函数在读入一个字符时 必须按一下 enter 键，该代码才会继续运行;
		//但是 getch() 函数读入一个字符时 不用 enter 代码会继续跑
		if (ch == 27) {
			work17 = 0;
			return -2;
		}
		if (a->index < 4 && a->index >= 0) {

		if (ch == 119 || ch == 115) {
			if (ch == 119) {//w 向上

				a->children[a->index]->setback();
				if (a->index == 0) {
					a->index = 3;
					a->children[a->index]->setActiveShine();
				}
				else {
					a->index--;
					a->children[a->index]->setActiveShine();
				}

			}

			else if (ch == 115) {//s 向下

				a->children[a->index]->setback();

				if (a->index == 3) {
					a->index = 0;
					a->children[a->index]->setActiveShine();
				}
				else {

					a->index++;
					a->children[a->index]->setActiveShine();

				}
			}
		}
		if (ch == '\r') {
			work17 = 0;
			return a->index;//按下enter健
		}
	}
		}
	return -1;
}
int keyboard_select_SceneMenu_shopwindow(DisplayObject* a,int& goldtrue) {
	DisplayObject* temp = a->children[3];
	static int work18 = 0; 
	if (work18 == 0) {

		temp->index = 0;//重置index否者会越外界
		temp->children[a->children[3]->index]->setActiveShine();
		work18 = 1;

	}
	char ch;
	if (_kbhit()) {//阻塞
		ch = _getch();//不用在控制台输出
		//getchar() 函数在读入一个字符时 必须按一下 enter 键，该代码才会继续运行;
		//但是 getch() 函数读入一个字符时 不用 enter 代码会继续跑
		if (ch == 27) {
			//work18 = 0;
			return -2;
		}
		if (temp->index < 6 && temp->index >= 0) {

			if (ch == 119 || ch == 115) {
				if (ch == 119) {//w 向上

					temp->children[temp->index]->setback();
					if (temp->index == 0) {
						temp->index = 5;
						temp->children[temp->index]->setActiveShine();
					}
					else {
						temp->index--;
						temp->children[temp->index]->setActiveShine();
					}

				}

				else if (ch == 115) {//s 向下

					temp->children[temp->index]->setback();

					if (temp->index == 5) {
						temp->index = 0;
						temp->children[temp->index]->setActiveShine();
					}
					else {

						temp->index++;
						temp->children[temp->index]->setActiveShine();

					}
				}
			}
			if (ch == '\r') {
				if (goldtrue >= temp->children[temp->index]->howmuch) {
					a->children[0]->visible = 1;//谢谢惠顾
					goldtrue -= temp->children[temp->index]->howmuch;
					return temp->index;//按下enter健购买了
				}
				else {
					a->children[1]->visible = 1;//金币不够
				}
				//work18 = 0;
				
			}
		}
	}
	return -1;
}