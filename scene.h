#pragma once
#include<vector>

#include"Database.h"
#include "DisplayObject.h"
//#include"Spritewindow.h"
using namespace std;
class DisplayObject;
class Sprite;
class TextDisplay;
class WindowMap;
class WindowShop;
class WindowBattleResult;
class Scene{
public:
	//Sceneactor的参数
	int dijige;//选择哪个英雄
	int keyboard_select_Sceneactor();
	void setActor(int id);
	void refresh();
	Actor* getActor();
	void setActor(Actor* actor);

	void drawParams(Actor* actor);
	void drawActorParams();
	DisplayObject* text;//黑框里面的内容
	void settext(int id);
	void settext(DisplayObject* text);

	//Scenemunc的参数
	void processok_Menu(int a);

	WindowMap* mapWindow;
	//WindowItem* itemWindow;
	//WindowSkill* skillWindow;
	WindowShop* shopWindow;

	//scenebattle的参数
	WindowBattleResult* battleResultWindow;
	void processback();
	int time;



	//WindowFile* saveWindow;
	void createWindowsSprites();
		void createMapWindow();
	/*void createItemWindow();
	void createSkillWindow();
	
	void createSaveWindow();*/
	void createShopWindow();

	Scene();
	Scene(int width, int height);
	Scene(int x, int y, int width, int height);
	void addChild(DisplayObject obj);
	void addChild(DisplayObject* obj);
	void removeChild(DisplayObject obj);
	void removeChild(DisplayObject* obj);

	virtual void render();
	virtual void render(char** data);
	virtual void quickRender(char**& data);
	virtual void requestPopScene();
	virtual void requestNextScene(Scene* scene);
	virtual bool isRequestPopScene();
	virtual Scene* getRequestNextScene();


	void paint(int x, int y, char c);
	char getData(int x, int y);
	vector<vector<char> > getData();

protected:
	void createContents();
	void clearContents();

	void updatePopScene();

	int x, y, z;
	int width, height;
	int gold;//金币
	bool requestPop;
	Scene* requestScene;

    //sceneactor的
	Actor* actor;
	Sprite* actorBigFace;
	Sprite* paramsDisplay;

	TextDisplay* textDisplay;
	
	

	vector<DisplayObject*> children;
	vector<vector<char> > data;
	vector<vector<char> > emptyData;
};



class SpriteCommandGroup;
class Scenestart :public Scene {
public:
//起始界面
	Scenestart();
	Sprite* titleCmd1;
	Sprite* titleCmd2;
	Sprite* titleCmd3;
	Sprite* titleCmBg;
	Sprite* background1;

	int cnt;
	
	//void updateOthers();
	//void updateSprites();
	//void updateControl();

	void createSprites();

	void createBackgroundSprites();
	void createCommandSprites();
	//void createLoadWindow();

	SpriteCommandGroup* commandGroup;
};
class Sceneactor : public Scene {
public:
	Sceneactor();

	
	void setupGame();
	void createArrowsSprites();
	void createSprites();
	void createGroundSprites();
	void createBigFaceSprites();
	void createParamsSprites();

	//void select(int id);
	void setActor(int id);
	void setActor(Actor* actor);
	Actor* getActor();
	Actor* actor;

	//void drawParams(Actor* actor);

	void refresh();
private:
	//int getCount();

	//void drawActorParams();
	//void scrollLeft();

	Sprite* leftArrow, * rightArrow;
	Sprite* background1;
};


class SceneMenu :public Scene {
public:
	SceneMenu(int shu1);

	bool anyWindowActive();
	//SpriteWindow* getActiveWindow();

private:
	bool okEnable();
	void processOK(int index);
	//void processBack();

	Sprite* actorBigFace1;
	Sprite* background1;

	Sprite* newEquip;
	Sprite* newSkill;
	Sprite* newer;

	SpriteCommandGroup* commandGroup1;

	//WindowMap* mapWindow;
	//WindowItem* itemWindow;
	//WindowSkill* skillWindow;
	//WindowShop* shopWindow;
	//WindowFile* saveWindow;
protected:
	void createSprites(int shu1);

	void createBackgroundSprites();
	void createBigFaceSprites(int shu1);
	void createCommandSprites();
	//void createWindowsSprites();
	void createNewPromptsSprites();

	

};
class objectenemys;
class scenebattle :public Scene {
public:
	scenebattle(int id, int level,int dijiba,int idactor);

	//void addEnemy(ObjectEnemy* enemy);
private:
	void battleEnd();

	int cnt, keyCd;
	bool pause;
	objectenemys* enemys;
	Sprite* battleResult;
	Sprite* battlePause;
	

	DisplayObject* battleField;
	
	Battle* battle;

protected:
	void update();

	void updateOthers();
	void updateBattleProcess();
	void updateBattleResult();
	void updateBattleResultAni();
	void updateBattlePause();

	void createSprites();
	
	void createBattleResult();
	void createBattlePause();

	void createtime();
	void createBattleField(int id);
	void createBattlers();
	void createBattleUI();
	void createActor(int id,int dijiba);
	void createEnemies(int level);
};