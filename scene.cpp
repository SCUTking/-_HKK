
#include "stdafx.h"

#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<ctime>
#include<algorithm>
#include"key.h"
#include<Windows.h>

#include"Database.h"
#include "scene.h"
#include"sprite.h"
#include"Spritecmd.h"
#include "DisplayObject.h"
#include "screenManager.h"
#include"Spritewindow.h"
#include"testplay.h"
#include"objectwar.h"
static int work4 = 0;//Scenemenu
static int work3 = 0;//SCeneactor
static int workd = 0;//�֣���������
static int work9 = 0;
static int work13 = 0;
static int work14 = 0;
Scene::Scene() {

	this->Scene::Scene(0, 0, ScreenManager::Width, ScreenManager::Height);
}
Scene::Scene(int width, int height) {
	this->Scene::Scene(0, 0, width, height);
}
Scene::Scene(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->gold = 0;

	this->actor = new Actor("Poword", "Actor1_bt.txt", "Actor1_true.txt");//sceneactor�Ĳ���
	this->dijige = 0;
	this->text = new DisplayObject(9, 9, 168, 132, Bitmap::getBitmap("text1.txt"));//��ʼ��
	this->text->wholewritedata2();
	actorBigFace = new Sprite(Bitmap::getBitmap(actor->bigFace));
	actorBigFace->x = 100;//�޸���һ��
	actorBigFace->ifactive = 2;
	paramsDisplay = new Sprite(Bitmap::getBitmap("ParamsDisplay.txt"));
	paramsDisplay->ifactive = 2;
	paramsDisplay->x=84; paramsDisplay->z = 100;
	paramsDisplay->y=((SHeight - paramsDisplay->resource->height) / 2);
	this->textDisplay= new TextDisplay(defaultFontFaceSmall);
	textDisplay->x = 14; textDisplay->y = 5;
	//paramsDisplay->addChild(textDisplay);
	//addChild(actorBigFace);






	createContents();
}

void Scene::createContents() {
	data.clear();
	vector<char> line;
	for (int x = 0; x < width; x++)
		line.push_back(' ');
	for (int y = 0; y < height; y++)
		data.push_back(line);
	emptyData = data;
}

void Scene::clearContents() {
	data = emptyData;/*
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			data[y][x] = ' ';*/
}

void Scene::addChild(DisplayObject obj) { addChild(&obj); }
void Scene::addChild(DisplayObject* obj) {//fdfgdjhgjhghhhhhhhhhhh
	children.push_back(obj);
	sort(children.begin(), children.end(), DisplayObjectComp);
}

void Scene::removeChild(DisplayObject obj) { removeChild(&obj); }
void Scene::removeChild(DisplayObject* obj) {
	vector<DisplayObject*>::iterator pos;
	pos = find(children.begin(), children.end(), obj);
	if (pos != children.end()) children.erase(pos);
}
void Scene::render() {
	clearContents();
	for (int i = 0; i < children.size(); i++) {
		DisplayObject* obj = children[i];
		obj->render(this, x + obj->x, y + obj->y);
	}
}
void Scene::render(char** data) {
	for (int i = 0; i < children.size(); i++) {
		DisplayObject* obj = children[i];
		obj->render(data, x + obj->x, y + obj->y);
	}
}
void Scene::requestPopScene() { requestPop = true; }
bool Scene::isRequestPopScene() { return requestPop; }

void Scene::requestNextScene(Scene* scene) { requestScene = scene; }
Scene* Scene::getRequestNextScene() { return requestScene; }
void Scene::updatePopScene() {
	requestPopScene();
	isRequestPopScene();
	if (isRequestPopScene()) ScreenManager::popScene();
}
void Scene::quickRender(char**& data) {
	//ִ����ȫ������Ⱦ


	for (int i = 0; i < children.size(); i++) {//Scene�Ķ���
		DisplayObject* obj = children[i];
		//*****************************************************************************************************************
		if (obj->ifactive == 1) //��������  work1   workd  workj time starty tempy
		{	
			static bool leftorright = 0;
			static int work1 = 0; static int workgold = 0;
			if (workgold == 0) {
				ScreenManager::goldtrue = 0;//���0
				workgold = 1;
			}
			if (work1<=children.size()) {
				obj->quickRender(data, x + obj->x, y + obj->y);//, 2, int(leftorright) + 1);
				work1++;
				
				return;
			}
			if (i == 0) {
				
				if (children[2]->children[1] ->visible!=1&& children[2]->children[2]->visible != 1) {
obj->children[1]->children[0]->setnumber(this->time--);
				}
				
				
				//this->time=10;
				obj->children[0]->updateRandomMove();//����ƶ�
					//���˽����󣬽�����Ϸ
				int deadnum = 0; 
				if (workd == 0) {
				for (int i = 0; i <obj->children[0]->children.size(); i++) {
					if (obj->children[0]->children[i]->isdead == 1) {
						deadnum++;
					}
					if (i == obj->children[0]->children.size()-1) {
						if (time == 0) {
							ScreenManager::goldtrue += (deadnum) * 60;//��ҼӼӼ�
							children[2]->children[0]->setnumber((deadnum) * 60);//windowresult�ĵ�һ������
							children[2]->visible = 1;
							children[2]->children[2]->visible = 1;//ʧ��
							//children[3]->visible = 1;
							workd = 1;
							break;
						}
						if (deadnum == obj->children[0]->children.size()) {
							ScreenManager::goldtrue += (deadnum) * 60;//��ҼӼӼ�
							children[2]->children[0]->setnumber((deadnum) * 60);//windowresult�ĵ�һ������
							children[2]->visible = 1;
							children[2]->children[1]->visible = 1;//ʤ��
							
							//children[3]->visible = 1;
							workd = 1;
							break;
						}
						
					}
				}
				//work1 = 0;//   workd  workj time starty tempy
				
				}
				if (workd == 1) {
						//work1 = 0;
						processback();

				}
				

			}
			obj->quickRender(data, x + obj->x, y + obj->y);
			
			if (i == 1) {
			//���������ƶ�
				static int workj = 0;//����
				static double time = 0; double v0 = 35;
				static int starty = 0;
				static int tempy = 0;
				if (workj == 1) {
					//����
					
					children[1]->y = starty-(v0*time-10 * time * time / 2);
					if (time + 1 > v0 / 10) {
						tempy = children[1]->y;
					}
					if (time >v0 / 10) {
						children[i]->y = tempy+10 * (time - v0 / 10) * (time - v0 / 10) / 2;
						time++;
						if (time >= 2 * v0 / 10) {
							children[i]->y = tempy + 10 * (time - v0 / 10) * (time - v0 / 10) / 2-31;
							workj = 0;

						}
					}
					time++;
					
					return;
				}
char a=keyboard_actor(obj);
			if (a == 'a') 
			{	
				obj->quickRender(data, x + obj->x, y + obj->y,2,int(leftorright)+1);
				leftorright = !leftorright;
				
			}
			if (a == 's') {
				obj->quickRender(data, x + obj->x, y + obj->y, 2, int(leftorright) + 1);
				leftorright = !leftorright;
				
			}
			if (a == 'w') {
				obj->quickRender(data, x + obj->x, y + obj->y, 2, int(leftorright) + 1);
				leftorright = !leftorright;
				
			}
			if (a == 'd') {
				obj->quickRender(data, x + obj->x, y + obj->y, 2, int(leftorright) + 1);
				leftorright = !leftorright;
			}
			if (a == 'j') {
				obj->ifbehitted(obj->x - 50, obj->y + 20, 7, children[0]);//�˺�
			}
			if (a == 'k') {
				time = 0;
				workj = 1;
				starty = obj->y;
			}
			//���µ�ͼ
			children[0]->spritemap(children[1]);//2Ϊ���0Ϊ��ͼ��
			}
		}
		//***********************************************************************************************************
		else if(obj->ifactive == 0) {//Scenestart
			static int work2 = 0;
			if (work2<2) {
				if (work2 == 1) {
				obj->children[0]->setActiveShine();	//��ʼѡ��startgame
				}

				obj->quickRender(data, x + obj->x, y + obj->y);
				work2++;
				if (work2 == 1) {
				continue;
				}
				if (work2 == 2) {
					obj->quickRender(data, x + obj->x, y + obj->y);
					return;
				}
			}
			
			
				if (i == 1) {
						int shu3 = keyboard_select_Scenestart(obj);
						obj->processok(shu3);
				}
				obj->quickRender(data, x + obj->x, y + obj->y);
				
				//obj->quickRender(data, x + obj->x, y + obj->y);
				
			
			
               // obj->quickRender(data, x + obj->x, y + obj->y);//�Ķ�ǰobj->quickRender(data, x + obj->x, y + obj->y)

		}
		else if (obj->ifactive == 3) {//scenemunc�� work4 work9 shu10 shu10_bt work13 work11 work14 

			
			if (work4<children.size()) {
				if (work4 == 2) {
				obj->children[0]->setActiveShine();	//��ʼѡ��"��ʼ��Ϸ��
				}
				obj->quickRender(data, x + obj->x, y + obj->y);
				work4++;
				if (work4 < 3) {
					continue;
				}
				if (work4 == 3) {
					obj->quickRender(data, x + obj->x, y + obj->y);
					work4++;//��ֹ�ڽ��и����ŵĶ���
					return;
				}
			}
			
			if (i == 2&&work9==0) {

				int shu = keyboard_select_SceneMenu(obj);
				if (shu != -1) {
						
						/*if (shu == 1) {
							return;//���ز˵�������Ⱦ
						}*/
						work9 = 1;
						this->processok_Menu(shu);
				}
					
			}
			obj->quickRender(data, x + obj->x, y + obj->y);
//***************************
			static int shu10 = 0; static int shu10_bt = 0;
			if (obj->chilrenifactive == 1&&obj->Displayactive) {//mapwindow
				if (work13 == 0) {
 shu10 = keyboard_select_SceneMenu_mapwindow(obj);
				}
				 if (shu10 == -1) {
					 static int work11 = 0;
					 if (work11 == 0) {
						 obj->children[shu10_bt]->shineDuration = -1;
						 obj->children[shu10_bt]->shineTransparent = 1;
						 obj->children[shu10_bt]->quickRender(data, obj->children[shu10_bt]->x + obj->x, obj->children[shu10_bt]->y + obj->y, 1);
						 work11 = 1;
					 }
					 else {
						 work11 = 0;
					 }
				 }
				 else {
					 if (shu10 >= 4) {//������enter

						
						 if (work14 == 0) {
						obj->children[5]->visible = 3;//maplevelwindow
						work14 = 1;
						work13 = 1;//������һ���ڵļ�������
							return;
						 }
						 else {

							 int shu14=keyboard_select_SceneMenu_maplevelwindow(obj->children[5]->children[5]);//mapwindow�е�maplevelwindow��spcmd*******��5ΪʲôΪ��5
							// obj->children[5]->children[3]->quickRender(data, x + obj->x, y + obj->y);
							 if (shu14 >= 0)//scenebattle�Ľ���
							 {
								 scenebattle* sb = new scenebattle(shu10-4, shu14,ScreenManager::dijibaScreen,ScreenManager::idactor);
								 ScreenManager::pushScene(sb);
							 }
							 else if (shu14 == -2) {
								 work4 = 0; //���ã���������ʱ����
								 work3 = 0;
								 mapWindow->Displayactive = false;
								 updatePopScene();
								 work9 = 0;
								 work13 = 0;
								 work14 = 0;
							 }
						 }
						 return;
					 }
				obj->children[shu10]->shineDuration = -1;
				obj->children[shu10]->shineTransparent = 1;
				obj->children[shu10]->quickRender(data, obj->children[shu10]->x+ obj->x, obj->children[shu10]->y + obj->y, 1);
				shu10_bt = shu10;
				 }
				 }
//******************************
			if (obj->chilrenifactive == 2 && obj->Displayactive) {
				
				obj->children[2]->setnumber(ScreenManager::goldtrue);
				int shu15 = keyboard_select_SceneMenu_shopwindow(obj,ScreenManager::goldtrue);//��ֵ�3����spritecommend��2����gold,0��okbuy��1��badbuy
				if (shu15 >= 0)//scenebattle�Ľ���
				{
					ScreenManager::dijibaScreen = shu15+1;//��1��û��bug
				}
				else if (shu15 == -2) {
					work4 = 0; //���ã���������ʱ����
					work3 = 0;
					mapWindow->Displayactive = false;
					updatePopScene();
					work9 = 0;
					work13 = 0;
				}
				}
//******************************
			}

		else if (obj->ifactive == 2) {//Sceneactor
			
			if (work3<children.size()) {
				
				obj->quickRender(data, x + obj->x, y + obj->y);
				work3++;
				continue;
			}
			obj->quickRender(data, x + obj->x, y + obj->y);
			if (i == children.size()-1) {


				int shu1 = keyboard_select_Sceneactor();//ѡ��Ӣ��

				if (shu1<0||shu1>3) {
					return;
							}
				else {
					ScreenManager::idactor = shu1;
				SceneMenu* scenemenu = new SceneMenu(shu1);
				ScreenManager::pushScene(scenemenu);
				return;
				}

			}
		}
	}
}
void Scene::paint(int x, int y, char c) {
	if (x >= 0 && x < width && y >= 0 && y < height)
		data[y][x] = c;
}
char Scene::getData(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height)
		return data[y][x];
	else
		return ' ';
}
vector<vector<char> > Scene::getData() { return data; }
//scenewindow��
void Scene::processok_Menu(int a) {
	


createWindowsSprites();
	switch (a)
	{
	case 0:
	{	mapWindow->visible = 1;
		mapWindow->Displayactive = true;
break;
	}
	case 1:
	{/*work4 = 0; //���ã���������ʱ����
	work3 = 0;
		mapWindow->Displayactive = false;
		updatePopScene();
		
		break;*/
		work4 = 0; //���ã���������ʱ����
		work3 = 0;
		mapWindow->Displayactive = false;

		work9 = 0;
		work13 = 0;
		work14 = 0;
		updatePopScene();
		break;
	}
	case 4:
	{
		shopWindow->visible = 1;
		shopWindow->Displayactive = true;
		break;
	}
	case 2:
	{
		work4 = 0; //���ã���������ʱ����
		work3 = 0;
		mapWindow->Displayactive = false;
		work9 = 0;
		work13 = 0;
		work14 = 0;
		updatePopScene();
		break;
	}
	case 3: {
		work4 = 0; //���ã���������ʱ����
		work3 = 0;
		mapWindow->Displayactive = false;
		
		work9 = 0;
		work13 = 0;
		work14 = 0;
		updatePopScene();
		break;
	}
	case 5: {
		exit(0);
		break;
	}
	

	default:
		break;
	}
}
void Scene::createWindowsSprites() {
	createMapWindow();
	createShopWindow();
	/*createItemWindow();
	createSkillWindow();
	
	createSaveWindow();*/
}
void Scene::createMapWindow() {
	mapWindow = new WindowMap();
	mapWindow->x = 0;
	mapWindow->z = 1000;
	mapWindow->visible = 0;
	mapWindow->ifactive = 3;
	mapWindow->chilrenifactive = 1;
	addChild(mapWindow);
}

void Scene::createShopWindow() {

	shopWindow = new WindowShop();
	shopWindow->x = 0;
	shopWindow->z = 1000;
	shopWindow->visible = 0;
	shopWindow->ifactive = 3;//������
	shopWindow->chilrenifactive = 2;//С����

	number* goldshop = new number(100, 12, defaultFontFaceSmall);//��� 90 155
	goldshop->x = 90;
	goldshop->y =155;
	goldshop->visible = 1;
	goldshop->setnumber(10000);
	shopWindow->addChild(goldshop);

	DisplayObject* okbuy = new DisplayObject(0, 0, 181, 47, Bitmap::getBitmap("AlertMsg2.txt"));//2
	okbuy->wholewritedata2();
	okbuy->x = 200;
	okbuy->y = 120;
	okbuy->visible = 0;
	shopWindow->addChild(okbuy);


	DisplayObject* badbuy = new DisplayObject(0, 0, 181, 47, Bitmap::getBitmap("AlertMsg1.txt"));//3
	badbuy->x = 200;
	badbuy->y = 120;
	badbuy->wholewritedata2();
	badbuy->visible = 0;
	shopWindow->addChild(badbuy);

	addChild(shopWindow);
}





//Sceneacyot��
int Scene::keyboard_select_Sceneactor()//���ұ����ǵ�һ���ڶ���
{
	
	char ch;
	if (_kbhit) {
		ch = _getch();//�����ڿ���̨���
		//getchar() �����ڶ���һ���ַ�ʱ ���밴һ�� enter �����ô���Ż��������;
		//���� getch() ��������һ���ַ�ʱ ���� enter ����������
		if (ch == 97 || ch == 100) {
			if (ch == 100) {//d ����
				

				if (dijige == 3) {
					dijige = 0;
					settext(dijige);
					setActor(dijige);

				}
				else {
					dijige++;
					settext(dijige);
					setActor(dijige);

					
				}

				children[3]->setActiveShine();
				children[2]->setActiveShine();
				//children[2]->setback();
				children[0]->quickRender(ScreenManager::data, x + children[0]->x, y + children[0]->y);
				children[2]->quickRender(ScreenManager::data, x + children[2]->x, y + children[2]->y);
				children[1]->quickRender(ScreenManager::data, x + children[1]->x, y + children[1]->y);
				children[3]->quickRender(ScreenManager::data, x + children[3]->x, y + children[3]->y);
				children[4]->quickRender(ScreenManager::data, x + children[4]->x, y + children[4]->y);
			}
			else if (ch == 97) {//a ����

				if (dijige == 0) {
					dijige = 3;
					settext(dijige);
					setActor(dijige);
					
				}
				else {
					dijige--;
					settext(dijige);
					setActor(dijige);
					
				}
				children[2]->setActiveShine();
				children[0]->quickRender(ScreenManager::data, x + children[0]->x, y + children[0]->y);
				children[2]->quickRender(ScreenManager::data, x + children[2]->x, y + children[2]->y);
				children[1]->quickRender(ScreenManager::data, x + children[1]->x, y + children[1]->y);
				children[3]->setActiveShine();
				children[3]->quickRender(ScreenManager::data, x + children[3]->x, y + children[3]->y);//�ұ�arrow�ᱻ����
				children[4]->quickRender(ScreenManager::data, x + children[4]->x, y + children[4]->y);
				
			}
			return -1;
		}
		if (ch == '\r') {//��б��\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
			if(dijige<4)
			return dijige;
		}
	}
}
void Scene::setActor(int id) { setActor(&actors[id]); }
void Scene::setActor(Actor* actor) {
	this->actor = actor; refresh();
}
void Scene::settext(int id) { settext(texts[id]); }
void Scene::settext(DisplayObject* text) {
	this->paramsDisplay->children[0] = text; //refresh();
}



Actor* Scene::getActor() {
	return actor;
}

void Scene::refresh() {
	actorBigFace->setBitmap(Bitmap::getBitmap(actor->bigFace));
	
	drawActorParams();
}

void Scene::drawActorParams() { drawParams(actor); }

void Scene::drawParams(Actor* actor) {
	char info_c[1000];
	string info;

	info = "- Select Actor -\n";
	info += "Name    " + actor->name;
	sprintf_s(info_c, "\nLEVEL   1\nMHP     %d\n           (*%.2f)\nMMP     %d\n           (*%.2f)\nATTACK  %d\n           (*%.2f)\nDEFENSE %d\n           (*%.2f)\nM. ATK  %d\n           (*%.2f)\nM. DEF  %d\n           (*%.2f)\nAGILITY %d\n           (*%.2f)\nLUCKY   %d\n           (*%.2f)\n",
		actor->params[0], actor->paramsGrowth[0],
		actor->params[1], actor->paramsGrowth[1],
		actor->params[2], actor->paramsGrowth[2],
		actor->params[3], actor->paramsGrowth[3],
		actor->params[4], actor->paramsGrowth[4],
		actor->params[5], actor->paramsGrowth[5],
		actor->params[6], actor->paramsGrowth[6],
		actor->params[7], actor->paramsGrowth[7]
	);
	textDisplay->setText(info += info_c);
}








Scenestart::Scenestart() {
	createSprites();
}
void Scenestart::createSprites() {
	cnt = 0;
	createBackgroundSprites();
	createCommandSprites();

}
void Scenestart::createBackgroundSprites() {

	background1 = new Sprite(Background3);
	background1->z = 0;
	background1->ifactive = 0;
	background1->visible = 1;
	addChild(background1);
}
void Scenestart::createCommandSprites() {
	commandGroup = new SpriteCommandGroup(titleCommandBg, 1, 0);
	commandGroup->ifactive = 0;
	commandGroup->visible = 1;
	this->addChild(commandGroup);//ΪScene���Ӻ���
//

	SpriteCommand* cmd;

	commandGroup->z = 0;
	commandGroup->x = 200;
	commandGroup->y = 100;

	cmd = commandGroup->addCommand(Bitmap::getBitmap("TitleCommand1.txt"));//�޸�startgame����ʼλ��
	cmd->x =100; cmd->y = 0;
	cmd = commandGroup->addCommand(Bitmap::getBitmap("TitleCommand2.txt"));//�޸�loadgame����ʼλ��
	cmd->x =100; cmd->y = 24;
	cmd = commandGroup->addCommand(Bitmap::getBitmap("TitleCommand3.txt"));//�޸�exitgame����ʼλ��
	cmd->x = 100; cmd->y = 48;

	//commandGroup->deactivate();

	
}





/**/
Sceneactor::Sceneactor() : Scene() {
	
	this->actor = new Actor("Poword", "Actor1_bt.txt", "Actor1_true.txt");
	this->dijige = 0;
	createSprites();
	//refresh();

}

void Sceneactor::createSprites() {
	
createGroundSprites();
    createBigFaceSprites();
	createArrowsSprites();
	createParamsSprites();
	
}
//void Sceneactor::select(int id) { index = id; setActor(id); }

void Sceneactor::setActor(int id) { setActor(&actors[id]); }
void Sceneactor::setActor(Actor* actor) {
	this->actor = actor; refresh();
}
Actor* Sceneactor::getActor() { 
	return actor;
}

void Sceneactor::refresh() {
	actorBigFace->setBitmap(Bitmap::getBitmap(actor->bigFace));
	drawActorParams();
}
void Sceneactor::createArrowsSprites() {

	
	Bitmap* arrow = Bitmap::getBitmap("Arrow.txt");
	rightArrow = new Sprite(arrow);
	rightArrow->x = 560;// SWidth - rightArrow->picturewidth;
	rightArrow->y = (SHeight - rightArrow->pictureheigth) / 2;
	rightArrow->z = 50;
	//���data2
	rightArrow->visible = 1;
	rightArrow->pictureheigth = rightArrow->resource->height;
	rightArrow->picturewidth = rightArrow->resource->width;
	rightArrow->createdata();
	rightArrow->wholewritedata2();
	rightArrow->ifactive = 2;

	leftArrow = new Sprite(arrow);
	leftArrow->x = 0; leftArrow->z = 50;
	leftArrow->y = (SHeight - leftArrow->pictureheigth) / 2;
	//���data2
	leftArrow->visible = 1;
	leftArrow->pictureheigth = rightArrow->resource->height;
	leftArrow->picturewidth = rightArrow->resource->width;
	leftArrow->createdata();
	leftArrow->getmirror(rightArrow);
	leftArrow->ifactive = 2;

	leftArrow->visible = 1;
	rightArrow->visible = 1;
	addChild(leftArrow);
	addChild(rightArrow);

}
void Sceneactor::createBigFaceSprites() {
	this->actorBigFace->visible=1;
	addChild(this->actorBigFace);
}
void Sceneactor::createGroundSprites() {
	background1 = new Sprite(Background3);
	background1->z = 0;
	background1->ifactive = 2;
	background1->visible = 1;
	addChild(background1);
}
void Sceneactor::createParamsSprites() {
	paramsDisplay->visible = 1;
	paramsDisplay->addChild(this->text);
	this->text->visible = 1;
	



	addChild(this->paramsDisplay);
	//addChild(this->textDisplay);
}






SceneMenu::SceneMenu(int shu1) : Scene() {
	createSprites(shu1);
}
void SceneMenu::createSprites(int shu1) {


    createBackgroundSprites();
	createBigFaceSprites(shu1);

    createCommandSprites();


	//createWindowsSprites();
	//createNewPromptsSprites();
}

void SceneMenu::createBackgroundSprites() {

	background1 = new Sprite(Background3);
	background1->z = 0;
	background1->ifactive = 3;
	background1->visible = 1;
	addChild(background1);

}

void SceneMenu::createBigFaceSprites(int shu1) {
	if (shu1 >= 0) {

	
	actorBigFace1 = new Sprite(actors[shu1].bigFace);//��vector��


	actorBigFace1->x =0;//����һ��
	actorBigFace1->z = 0;

	actorBigFace1->ifactive = 3;
	actorBigFace1->visible = 1;
	addChild(actorBigFace1);

	}
}
void SceneMenu::createCommandSprites() {

	commandGroup1 = new SpriteCommandGroup(menuCommandBg, 2, 0);//vectorLine: 1463�������ǲ����������
	SpriteCommand* cmd;

	commandGroup1->z = 50;
	commandGroup1->y = 25;

	cmd = commandGroup1->addCommand(Bitmap::getBitmap("��ʼ��Ϸ.txt"));//�ַ�
	cmd->x = 100; cmd->y = 0; cmd->z = 0;
	cmd = commandGroup1->addCommand(Bitmap::getBitmap("MenuCommand2.txt"));//�ҵı���
	cmd->x = 100; cmd->y = 40; cmd->z = 0;
	cmd = commandGroup1->addCommand(Bitmap::getBitmap("MenuCommand3.txt"));//�ҵļ���
	cmd->x = 100; cmd->y = 60; cmd->z = 0;
	cmd = commandGroup1->addCommand(Bitmap::getBitmap("MenuCommand4.txt"));//�̵�
	cmd->x = 100; cmd->y = 80; cmd->z = 0;
	cmd = commandGroup1->addCommand(Bitmap::getBitmap("MenuCommand5.txt"));//������Ϸ
	cmd->x = 100; cmd->y = 100; cmd->z = 0;
	cmd = commandGroup1->addCommand(Bitmap::getBitmap("MenuCommand6.txt"));//����
	cmd->x = 100; cmd->y = 20; cmd->z = 0;

	/*commandGroup->setActiveShake(false);
	commandGroup->setActiveShineChar('*');
	commandGroup->deactivate();*/
	commandGroup1->x = 320;//SWidth - commandGroup->getWidth();
	commandGroup1->ifactive = 3;
	commandGroup1->visible = 1;
	addChild(commandGroup1);


}

void SceneMenu::createNewPromptsSprites() {
	newEquip = new Sprite(Bitmap::getBitmap("NewEquipPrompt.txt"));
	newSkill = new Sprite(Bitmap::getBitmap("NewSkillPrompt.txt"));
	newer = new Sprite(Bitmap::getBitmap("NewerPrompt.txt"));

	newEquip->x = 0; newEquip->y = SHeight - newEquip->getSpriteHeight();//��̫���׵�
	newSkill->x = 0; newSkill->y = SHeight - newEquip->getSpriteHeight();
	newer->x = newer->y = 0;
	newEquip->z = newSkill->z = newer->z = 500;
	newEquip->visible = newSkill->visible = newSkill->visible = 1;//0�ĳ�1
	addChild(newEquip);
	addChild(newSkill);
	addChild(newer);
}



scenebattle::scenebattle(int id, int level,int dijiba,int idactor)
{	
	createBattleField(id);
	createEnemies(level);
	createActor(idactor,dijiba);
	createBattleResult();
	//createtime();
}
void scenebattle::createtime() {
}
void scenebattle::createActor(int idactor,int dijiba)
{//����
	weapon* weapon1 = new weapon(150, 70,dijiba,Bitmap::getBitmap("Weapons1.txt"));
	
	weapon1->visible = 1; weapon1->x = -50; weapon1->y = 0;

	DisplayObject* b = new DisplayObject(0, 0, 100, 70, Bitmap::getBitmap(actors[idactor].fileName));
	b->x = 400; b->y = 110;//��ʼλ��
	b->dijiba = dijiba;//�����õ�
	b->addChild(weapon1);//��

	b->ifactive = 1; this->addChild(b);
}
void scenebattle::createEnemies(int level)
{	
	this->enemys = new objectenemys();
	int enemysum = 0;

	//ʱ��
	//����scenebattleʱ��
	if (level == 3) {
		this->time = 600;//30 - level * 4;//�м�
		enemysum = 7;
	}
	if (level == 2) {
		this->time = 200;//30 - level * 4;//
		enemysum = 16;
	}
	if (level == 1) {
		this->time = 400;//30 - level * 4;
		enemysum = 10;
	}
	if (level == 0) {
		this->time = 800;//30 - level * 4;
		enemysum = 4;
	}


	for (int i = 0; i < enemysum; i++) {
		Object* c = new Object(80, 60, Bitmap::getBitmap("Enemy2.txt"));
		c->ismove = 1;
		c->x = 510 + rand() % 11 - 5; c->y = 230 + rand() % 11 - 5;
		c->isdead = 0;
		enemys->addChild(c);
	}

	DisplayObject* time = new DisplayObject(300, 150, 150, 25, Bitmap::getBitmap("time.txt"));
	time->wholewritedata2();
	time->setback();
	time->visible = 1;
	number* time1= new number(50, 12, defaultFontFaceSmall);
	time1->x = 90; time1->y = 8;
	time1->visible = 1;
	time->addChild(time1); //battleField�ĵڶ����ĵ�һ��

	



	this->enemys->visible = 1;
	this->enemys->ifactive = 1;
	battleField->addChild(enemys);//�ڵ�ͼ����Ⱦ����
	battleField->addChild(time);//
}
void scenebattle::createBattleField(int id) {
	this->battleField = new DisplayObject(0, 0, 800, 400, battles[id]);
	this->battleField->wholewritedata2();//��ͼƬд��
	this->battleField->visible = 1;
	this->battleField->ifactive = 1;
	//this->battleField->x = -600;//��������
	//this->battleField->y = -200;
	this->addChild(battleField);
}
void scenebattle::createBattleResult() {
	//background = new Sprite(battle->battleField.fileName);
	//addChild(background);
	battleResult = new Sprite();
	battleResult->z = 50;

	battleResultWindow = new WindowBattleResult();
	battleResultWindow->x =110;
	battleResultWindow->y = 50;
	battleResultWindow->z = 40;
	
	battleResultWindow->goldGain = new number(100,12,defaultFontFaceSmall);
	battleResultWindow->goldGain->x = 150;
	battleResultWindow->goldGain->y = 71;
	battleResultWindow->goldGain->visible = 1;
	DisplayObject* bwin = new DisplayObject(10, 100, 290, 42, Bitmap::getBitmap("BattleWin.txt"));
	bwin->wholewritedata2();
	bwin->visible = 0;
	DisplayObject* blose = new DisplayObject(10, 100, 290, 42, Bitmap::getBitmap("BattleLose.txt"));
	blose->wholewritedata2();
	blose->visible = 0;
	battleResultWindow->addChild(battleResultWindow->goldGain);//1111
	battleResultWindow->addChild(bwin);//2222
	battleResultWindow->addChild(blose);//3333
	//battleResultWindow->deactivate();
	battleResult->visible = battleResultWindow->visible = 0;


	battleResult->ifactive = 1; battleResultWindow->ifactive = 1;
	//addChild(battleResult);
	addChild(battleResultWindow);
}


void Scene::processback() {//����ս�������������
	char ch;

	if (_kbhit()) {
		ch = _getch();
		if (ch == '\r') {
	workd = 0;
		updatePopScene();
		}
	
	}
	else {
		return;
	}
}