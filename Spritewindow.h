#pragma once

#include"SpriteVB.h"
#include"Sprite.h"
#include"Spritecmd.h"
//#include"GameManager.h"
#include"Database.h"
//#include"DataManager.h"
class SpriteWindow : public Sprite {
public:
	SpriteWindow();
	SpriteWindow(Bitmap* background);
	virtual void refresh();

	virtual void activate();
	virtual void deactivate();
	bool isActive();

private:
	bool active;
protected:
	virtual void initialize();
	virtual void setup();

	virtual void updateOthers();
	virtual void updateControl();

	virtual void processOK();
	virtual void processBack();

	int keyCd;
};


class WindowMapLevel : public SpriteWindow {
public:
	static const int MapPicPos[2];
	static const int LevelSelectPos[2];
	static const int DifficultyPos[2];
	static const int HighRecordPos[2];
	static const int JudgePos[2];
	static const string JudgeString[8];

	WindowMapLevel();
	~WindowMapLevel();

	void setMap(int i);
	void setMap(Battle* battle);

	virtual void activate();
	virtual void deactivate();

private:
	virtual void initializeMapInfo();
	virtual void initializeLevelCommands();
	virtual void initializeMapPic();

	virtual void refreshMapInfo();
	virtual void refreshMapPic();

	Battle* map;
	Sprite* mapPic, * mapNames;
	TextDisplay* judgeRecord, * difficulty;
	NumberDisplay* scoreRecord;

	SpriteCommandGroup* levelCommandGroup;
protected:
	virtual void initialize();
	virtual void setup();
	virtual void refresh();

	virtual void updateOthers();
	virtual void updateControl();

	virtual void processOK();

};
class WindowMap : public SpriteWindow {
public:
	static const int MapPos[System::MaxMapCount][2];
	static const string MapPicFiles[System::MaxMapCount][2];
	WindowMap();
	~WindowMap();

	virtual void activate();
	virtual void deactivate();

	void select(int id);
	void deselect();
	void deselect(int id);

private:
	virtual void initializeMapCommands();
	virtual void initializeMapLevelSelect();

	void updateNameDisplay();

	void scrollUp();
	void scrollDown();
	void scrollLeft();
	void scrollRight();

	int index;
	Sprite* mapNames;
	SpriteCommand* mapCommands[System::MaxMapCount];
	WindowMapLevel* levelSelectWindow;
protected:
	virtual void initialize();
	virtual void setup();

	virtual void updateOthers();
	virtual void updateControl();

	virtual void processOK();

};

class WindowItem : public SpriteWindow {
public:
	static const int EquipPos[System::EquipCount][2];
	static const int ParamsPos[System::BaseParamCount - 2][2];
	static const int ShortCutPos[2];
	static const int ActorNamePos[2];
	static const int GoldTextPos[2];
	static const int PageTextPos[2];
	static const int ItemBlockPos[2];
	static const Rect HPRect;
	static const Rect MPRect;

	WindowItem();
	~WindowItem();

	void refresh();

	void activate();
	void deactivate();

	void changePage(int index);
	int maxPage();

	bool isEquipSelecting();
private:
	void initializeMHPBlock();
	void initializeItemBlock();
	void initializeParamsBlock();
	void initializeEquipBlock();
	void initializeShortItemsBlock();
	void initializeTips();

	void refreshMHPBlock();
	void refreshItemBlock();
	void refreshPrarmsBlock();
	void refreshEquipBlock();
	void refreshShortItemsBlock();

	int pageItemCount();
	int itemYSpacing();

	void makeItemsList();
	void clearItemsList();

	void drawItem(int index);
	void clearItem(int index);

	void drawPageCount();

	void drawAllItems();
	void clearAllItems();

	void processOK();
	void processBind(int sIndex);

	void switchGroup();
	void scrollLeft();
	void scrollRight();

	int pageIndex;
	bool equipFrame;

	//ObjectActor* actor;

	NumberDisplay* paramsText[System::BaseParamCount - 2];
	TextDisplay* nameText, * pageText;
	NumberDisplay* goldText;

	Sprite* tipsDisplay;

	SpriteVarBar* hpBar, * mpBar;
	SpriteCommandGroup* equipsGroup;
	SpriteCommandGroup* itemsGroup;
	//Sprite* shortItems[GameManager::ItemSlotCount];
	vector<ItemBase*> equipData;
	vector<vector<ItemBase*>> pageData;

protected:
	void initialize();
	void setup();

	//void updateOthers();
	void updateControl();
};

class WindowSkill : public SpriteWindow {
public:
	static const int ShortCutPos[2];
	static const int PageTextPos[2];
	static const int SkillBlockPos[2];
	static const Rect HPRect;
	static const Rect MPRect;

	WindowSkill();
	~WindowSkill();

	void refresh();

	void activate();
	void deactivate();

	void changePage(int index);
	int maxPage();

private:
	void initializeMHPBlock();
	void initializeSkillBlock();
	void initializeShortSkillsBlock();
	void initializeTips();

	void refreshMHPBlock();
	void refreshSkillBlock();
	void refreshShortSkillsBlock();

	int pageItemCount();
	int itemYSpacing();

	void makeItemsList();
	void clearItemsList();

	void drawItem(int index);
	void clearItem(int index);

	void drawPageCount();

	void drawAllItems();
	void clearAllItems();

	void processOK();
	void processBind(int sIndex);

	void scrollLeft();
	void scrollRight();

	int pageIndex;

	//ObjectActor* actor;

	TextDisplay* pageText;

	Sprite* tipsDisplay;

	SpriteVarBar* hpBar, * mpBar;
	SpriteCommandGroup* skillsGroup;
	//Sprite* shortSkills[GameManager::SkillSlotCount];
	vector<vector<Skill*>> pageData;

protected:
	void initialize();
	void setup();

	void updateControl();
};


class WindowShop : public SpriteWindow {
public:
	static const int GoldTextPos[2];
	static const int PriceTextPos[2];
	static const int HoldTextPos[2];
	static const int CountTextPos[2];
	static const int SumTextPos[2];
	static const int PageTextPos[2];
	static const int GoodBlockPos[2];
	static const int AlertPos[2];
	static const int CatPosX;

	WindowShop();
	void initialize();
	void initializegoods();
	//WindowShop(int id);
	//WindowShop(Shop* shop);
	//~WindowShop();

	//void refresh();

	//void activate();
	//void deactivate();

	//void changePage(int index);
	//int maxPage();

	//void setCatPattern(Bitmap* catPattern);
	//void alertMsg(Bitmap* alertContents);
	//void closeAlertMsg();

	//int getAutoSelectShop();

	//void setShop(int id);
	//void setShop(Shop* shop);

	//ItemBase* getItem();

private:
	//void initializeGoodBlock();
	//void initializeGoodInfoBlock();
	//void initializeGoldBlock();
	//v//oid initializeCat();
	//void initializeTips();

	//void refreshGoodBlock();
	//void refreshGoodInfoBlock();
	//void refreshGoldBlock();

	//int pageItemCount();
	//int itemYSpacing();

	//void makeItemsList();
	//void clearItemsList();

	//void drawItem(int index);
	// clearItem(int index);

	//void drawPageCount();

	//void drawAllItems();
	//void clearAllItems();

	//void processOK();
	//void processBack();

	//void scrollLeft();
	//void scrollRight();

	int pageIndex;
	int count;
	bool buyFlag;

	Shop* shop;

	TextDisplay* pageText;
	NumberDisplay* priceText;
	NumberDisplay* holdText;
	NumberDisplay* sumText;
	NumberDisplay* goldText;
	//TypableNumberDisplay* countText;

	Sprite* tipsDisplay;
	Sprite* cat, * alert;

	SpriteCommandGroup* goodsGroup;
	vector<vector<ItemBase*>> pageData;

protected:
	//void initialize();
	//void setup();

	//void updateOthers();
	//void updateControl();
	//void updateAlert();
};
class WindowFile : public SpriteWindow {
public:
	//static const int FilePos[DataManager::MaxSaveFileCount][2];
	static const int LeaderNamePos[2];
	static const int LeaderLevelPos[2];
	static const int GoldPos[2];
	static const int DateTimePos[2];
	WindowFile(bool onlyLoad = false);
	~WindowFile();

	virtual void activate();
	virtual void deactivate();

	bool isOnlyLoad();
	void select(int id);
	void deselect();
	void deselect(int id);

	void deleteGame();
	void loadGame();
	void saveGame();

private:
	virtual void initializeFileInfo();
	virtual void initializeFileCommands();
	virtual void initializeTips();

	virtual void refreshFileInfo();
	virtual void refreshFileCommands();

	virtual void refreshFileCommandBitmap(int id);

	void scrollUp();
	void scrollDown();
	void scrollLeft();
	void scrollRight();

	int index;
	bool onlyLoad;

	Sprite* tipsDisplay;
	TextDisplay* name, * time;
	NumberDisplay* level, * gold;


protected:
	virtual void initialize();
	virtual void setup();
	virtual void refresh();

	virtual void updateOthers();
	virtual void updateControl();

	virtual void processOK();

};
class WindowBattleResult : public SpriteWindow {
public:
	static const int TimeNeedPos[2];
	static const int RecoverPointPos[2];
	static const int BeHurtPointPos[2];
	static const int HurtPointPos[2];
	static const int DifficultPos[2];
	static const int FinalScorePos[2];
	static const int GoldGainPos[2];
	static const int JudgePos[2];
	static const string JudgeFileName[7];
	static const int GoldTextAniDuration = 50;

	WindowBattleResult();
	~WindowBattleResult();

	void setup();
	void refresh();

	void requestPopScene();
	bool popSceneRequest();

private:
	void initializeParams();

	void refreshParams();

	void processOK();
	void processBack();

	bool popScene;
	bool setuped;
	int duration;
	

	NumberDisplay* timeNeed;
	NumberDisplay* recoverPoint;
	NumberDisplay* beHurtPoint;
	NumberDisplay* hurtPoint;
	NumberDisplay* finalScore;
	
	TextDisplay* difficulty;

	Sprite* judge;
protected:
	void initialize();

	void updateOthers();
	void updateTextAni();

	void updateGoldAni();
	void updateJudgeAni();

};

