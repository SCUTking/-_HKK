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
	//���ص�
	obj->children[0]->visible = 0;
	//��ԭ��ɫ
	obj->writedata2(2, 1);
	sum = 0;
	}

	int uplineY = 105; int downlineY = 185; int walkspeed = 8;
	char ch;
	if (_kbhit()) {
		ch = _getch();//�����ڿ���̨���
		//getchar() �����ڶ���һ���ַ�ʱ ���밴һ�� enter �����ô���Ż��������;
		//���� getch() ��������һ���ַ�ʱ ���� enter ����������
		if (ch == 119 || ch == 115 || ch == 100 || ch == 97||ch=='j'||ch=='k') {
			if (ch == 119) {//w ����
				if (obj->y+obj->pictureheigth-walkspeed>=uplineY)
				{
				obj->y -= 8;
				return 'w';
				}
				
			}
			else if (ch == 115) {//s ����
				if (obj->y + obj->pictureheigth +walkspeed <= downlineY) {
				obj->y += 8;
				return 's';
				}

			}
			else if (ch == 100) {//d ����
				if (obj->x < 800-8) {
				obj->x += 8;
				return 'd';
				}

			}
			else if (ch == 97) {//a ����
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
	else {//û�м��̵����뺯������ fffffff
		return 'f';
	}
}


int keyboard_select_Scenestart(DisplayObject* a) {

	char ch;
	if (_kbhit) {
		ch = _getch();//�����ڿ���̨���
		//getchar() �����ڶ���һ���ַ�ʱ ���밴һ�� enter �����ô���Ż��������;
		//���� getch() ��������һ���ַ�ʱ ���� enter ����������
		if (ch == 119 || ch == 115 ) {
			if (ch == 115) {//w ����
				
	a->children[a->index]->setback();
				if (a->index == 0) {
					a->index = 2;
					a->children[a->index]->setActiveShine();
				}
				else {
					a->index--;
					a->children[a->index]->setActiveShine();
				}
			//***************************************************************w��s���˲��ܳɹ�
			}
			else if (ch == 119) {//s ����
				
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
			return a->index;//����enter��
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
		ch = _getch();//�����ڿ���̨���
		//getchar() �����ڶ���һ���ַ�ʱ ���밴һ�� enter �����ô���Ż��������;
		//���� getch() ��������һ���ַ�ʱ ���� enter ����������
		if (ch == 119 || ch == 115) {
			if (ch == 119) {//w ����

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
			else if (ch == 115) {//s ����

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
			return a->index;//����enter��
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
		a->index = 0;//mapwindow�ĵ�һ����ͼ
		work7 = 1;
		return a->index;
	}
	char ch;
	if (_kbhit()) {
		ch = _getch();//�����ڿ���̨���
		//getchar() �����ڶ���һ���ַ�ʱ ���밴һ�� enter �����ô���Ż��������;
		//���� getch() ��������һ���ַ�ʱ ���� enter ����������
		if (ch == 119 || ch == 115 || ch == 100 || ch == 97) {
			if (ch == 119) {//w ����
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
			else if (ch == 115) {//s ����

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
			return a->index+4;//����enter�� ��һ����һ��
		}
	}
		return -1;
}

int keyboard_select_SceneMenu_maplevelwindow(DisplayObject* a) {
	static int work17 = 0;
	if (work17 == 0) {
		a->children[a->index]->setActiveShine();//����
		a->children[a->index]->setback();//����
		a->index = 0;//����index���߻�Խ���
		a->children[a->index]->setActiveShine();
		work17 = 1;
		
	}
	char ch;
	if (_kbhit()) {//����
		ch = _getch();//�����ڿ���̨���
		//getchar() �����ڶ���һ���ַ�ʱ ���밴һ�� enter �����ô���Ż��������;
		//���� getch() ��������һ���ַ�ʱ ���� enter ����������
		if (ch == 27) {
			work17 = 0;
			return -2;
		}
		if (a->index < 4 && a->index >= 0) {

		if (ch == 119 || ch == 115) {
			if (ch == 119) {//w ����

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

			else if (ch == 115) {//s ����

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
			return a->index;//����enter��
		}
	}
		}
	return -1;
}
int keyboard_select_SceneMenu_shopwindow(DisplayObject* a,int& goldtrue) {
	DisplayObject* temp = a->children[3];
	static int work18 = 0; 
	if (work18 == 0) {

		temp->index = 0;//����index���߻�Խ���
		temp->children[a->children[3]->index]->setActiveShine();
		work18 = 1;

	}
	char ch;
	if (_kbhit()) {//����
		ch = _getch();//�����ڿ���̨���
		//getchar() �����ڶ���һ���ַ�ʱ ���밴һ�� enter �����ô���Ż��������;
		//���� getch() ��������һ���ַ�ʱ ���� enter ����������
		if (ch == 27) {
			//work18 = 0;
			return -2;
		}
		if (temp->index < 6 && temp->index >= 0) {

			if (ch == 119 || ch == 115) {
				if (ch == 119) {//w ����

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

				else if (ch == 115) {//s ����

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
					a->children[0]->visible = 1;//лл�ݹ�
					goldtrue -= temp->children[temp->index]->howmuch;
					return temp->index;//����enter��������
				}
				else {
					a->children[1]->visible = 1;//��Ҳ���
				}
				//work18 = 0;
				
			}
		}
	}
	return -1;
}