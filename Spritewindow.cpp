#include"stdafx.h"
#include "SpriteWindow.h"
#include "Database.h"
//#include "GameManager.h"
//#include "ObjectBattler.h"
#include "ScreenManager.h"

const int WindowMap::MapPos[System::MaxMapCount][2] = {
	{ 4,20 },{ 204,20 },{ 4,95 },{ 204,95 }
};
const string WindowMap::MapPicFiles[System::MaxMapCount][2] = {
	{ "Battle1_small.txt","Battle1_name.txt" },
	{ "Battle2_small.txt","Battle2_name.txt" },
	{ "Battle3_small.txt","Battle3_name.txt" },
	{ "Battle4_small.txt","Battle4_name.txt" }
};

const int WindowMapLevel::MapPicPos[2] = { 15,28 };
const int WindowMapLevel::LevelSelectPos[2] = { 10,120 };
const int WindowMapLevel::DifficultyPos[2] = { 300,40 };
const int WindowMapLevel::HighRecordPos[2] = { 300,51 };
const int WindowMapLevel::JudgePos[2] = { 300,62 };
const string WindowMapLevel::JudgeString[8] = { "SSS","SS","S","A","B","C","D","--" };

const int WindowItem::EquipPos[System::EquipCount][2] = {
	{ 0,110 },{ 55,33 },{ 55,82 },{ 55,141 },{ 4,21 },{ 4,41 },{ 2,146 }
};
const int WindowItem::ParamsPos[System::BaseParamCount - 2][2] = {
	{ 164,142 },{ 164,149 },{ 164,157 },{ 284,142 },{ 284,149 },{ 284,157 }
};
const int WindowItem::ShortCutPos[2] = { 366,60 };
const int WindowItem::ActorNamePos[2] = { 166,134 };
const int WindowItem::GoldTextPos[2] = { 292,125 };
const int WindowItem::PageTextPos[2] = { 212,125 };

const int WindowItem::ItemBlockPos[2] = { 148, 27 };
const Rect WindowItem::HPRect = Rect(234, 0, 128, 8);
const Rect WindowItem::MPRect = Rect(234, 10, 128, 8);

const int WindowSkill::ShortCutPos[2] = { 317,43 };
const int WindowSkill::PageTextPos[2] = { 13,157 };
const int WindowSkill::SkillBlockPos[2] = { 13, 27 };
const Rect WindowSkill::HPRect = Rect(234, 0, 128, 8);
const Rect WindowSkill::MPRect = Rect(234, 10, 128, 8);


const int WindowShop::GoldTextPos[2] = { 94,156 };
const int WindowShop::PriceTextPos[2] = { 280,39 };
const int WindowShop::HoldTextPos[2] = { 280,51 };
const int WindowShop::CountTextPos[2] = { 280,63 };
const int WindowShop::SumTextPos[2] = { 280,75 };
const int WindowShop::PageTextPos[2] = { 134,24 };
const int WindowShop::GoodBlockPos[2] = { 9,35 };
const int WindowShop::AlertPos[2] = { 128,56 };
const int WindowShop::CatPosX = 268;


/*const int WindowFile::FilePos[DataManager::MaxSaveFileCount][2] = {
	{ 7,42 },{ 117,42 },{ 7,97 },{ 117,97 }
};*/
const int WindowFile::LeaderNamePos[2] = { 228,51 };
const int WindowFile::LeaderLevelPos[2] = { 228,75 };
const int WindowFile::GoldPos[2] = { 228,99 };
const int WindowFile::DateTimePos[2] = { 228,123 };

const int WindowBattleResult::TimeNeedPos[2] = { 76,17 };
const int WindowBattleResult::HurtPointPos[2] = { 76,33 };
const int WindowBattleResult::DifficultPos[2] = { 76,49 };
const int WindowBattleResult::RecoverPointPos[2] = { 261,17 };
const int WindowBattleResult::BeHurtPointPos[2] = { 261,33 };
const int WindowBattleResult::FinalScorePos[2] = { 261,49 };
const int WindowBattleResult::GoldGainPos[2] = { 121,70 };
const int WindowBattleResult::JudgePos[2] = { 273,41 };
const string WindowBattleResult::JudgeFileName[7] = {
	"BattleJudge_sss.txt",
	"BattleJudge_ss.txt",
	"BattleJudge_s.txt",
	"BattleJudge_a.txt",
	"BattleJudge_b.txt",
	"BattleJudge_c.txt",
	"BattleJudge_d.txt"
};




SpriteWindow::SpriteWindow() {}
SpriteWindow::SpriteWindow(Bitmap* background) : Sprite(background) {
	initialize(); setup(); refresh();
}
void SpriteWindow::initialize() {}
void SpriteWindow::refresh() {}
void SpriteWindow::setup() {}

bool SpriteWindow::isActive() { return active; }

void SpriteWindow::activate() {
	refresh(); active = true; keyCd = 10;
}
void SpriteWindow::deactivate() {
	active = false;
}

void SpriteWindow::processOK() {}
void SpriteWindow::processBack() {
	deactivate();
}

void SpriteWindow::updateOthers() {
	//Sprite::updateOthers();
	updateControl();
}
void SpriteWindow::updateControl() {
	if (--keyCd > 0 || !isActive()) return;
}


WindowMap::WindowMap() :SpriteWindow(menuMapBackground) {
	initialize(); setup(); refresh();
}
WindowMap::~WindowMap() {
	delete mapNames;
	delete levelSelectWindow;
	for (int i = 0; i < System::MaxMapCount; i++)
		delete mapCommands[i];
}
void WindowMap::initialize() {
	SpriteWindow::initialize();
	initializeMapCommands();
	initializeMapLevelSelect();
}
void WindowMap::setup() {
	SpriteWindow::setup();
	index = 0;
	
}
void WindowMap::initializeMapCommands() {
	for (int i = 0; i < System::MaxMapCount; i++) {//4个

		mapCommands[i] = new SpriteCommand(Bitmap::getBitmap(MapPicFiles[i][0]),14,false);//new Bitmap(0,0) 最后一位的重载函数导致
																						//data2为空
		mapCommands[i]->x = MapPos[i][0]; mapCommands[i]->y = MapPos[i][1];
		mapCommands[i]->visible = 1;
	
		addChild(mapCommands[i]);
	}

	mapNames = new Sprite();
	mapNames->z = 50;
	mapNames->visible = 1;
	addChild(mapNames);//5个
}
void WindowMap::initializeMapLevelSelect() {
	levelSelectWindow = new WindowMapLevel();//6个
	levelSelectWindow->z = 10000;
	
	addChild(levelSelectWindow);
}
void WindowMap::activate() {
	SpriteWindow::activate(); mapCommands[index]->activate();
}
void WindowMap::deactivate() {
	SpriteWindow::deactivate(); mapCommands[index]->deactivate();
}
void WindowMap::select(int id) {
	
}
void WindowMap::deselect() { deselect(index); }
void WindowMap::deselect(int id) { //if (System::MaxMapCount > id) mapCommands[id]->deselect();
 }

void WindowMap::scrollUp() {
	int id = (index - 2 + System::MaxMapCount) % System::MaxMapCount;
	select(id);
}
void WindowMap::scrollDown() {
	int id = (index + 2) % System::MaxMapCount;
	select(id);
}
void WindowMap::scrollLeft() {
	int id = (index - 1 + System::MaxMapCount) % System::MaxMapCount;
	select(id);
}
void WindowMap::scrollRight() {
	int id = (index + 1) % System::MaxMapCount;
	select(id);
}

void WindowMap::processOK() {
	SpriteWindow::processOK();
	levelSelectWindow->activate();
	levelSelectWindow->setMap(index);
	//ScreenManager::pushScene(new SceneBattle(index));
}
void WindowMap::updateNameDisplay() {
	mapNames->setBitmap(Bitmap::getBitmap(MapPicFiles[index][1]));
	mapNames->x = mapCommands[index]->x;
	mapNames->y = mapCommands[index]->y +
		mapCommands[index]->getSpriteHeight() -
		mapNames->getSpriteHeight();
}

void WindowMap::updateOthers() {
	SpriteWindow::updateOthers();
	updateControl();
}
void WindowMap::updateControl() {
	SpriteWindow::updateControl();
	if (levelSelectWindow->isActive()) return;
	if (keyCd > 0 || !isActive()) return;

}



WindowMapLevel::WindowMapLevel() :SpriteWindow(menuMapLevelBackground) {

	initialize(); setup(); setMap(NULL); //refresh();
}
WindowMapLevel::~WindowMapLevel() {
	delete mapPic, mapNames, judgeRecord;
	delete difficulty, scoreRecord;
	delete levelCommandGroup;
}
void WindowMapLevel::initialize() {
	SpriteWindow::initialize();
	initializeMapInfo();
	initializeLevelCommands();
	initializeMapPic();
}
void WindowMapLevel::setup() {
	SpriteWindow::setup();
	deactivate();
}
void WindowMapLevel::setMap(int i) {
	//setMap(&battles[i]);
}
void WindowMapLevel::setMap(Battle* battle) {
	if (map != battle) { map = battle; refresh(); }
}

void WindowMapLevel::initializeMapInfo() {
	difficulty = new TextDisplay(defaultFontFaceSmall);
	difficulty->x = DifficultyPos[0];
	difficulty->y = DifficultyPos[1];

	scoreRecord = new NumberDisplay(defaultFontFaceSmall);
	scoreRecord->x = HighRecordPos[0];
	scoreRecord->y = HighRecordPos[1];

	judgeRecord = new TextDisplay(defaultFontFaceSmall);
	judgeRecord->x = JudgePos[0];
	judgeRecord->y = JudgePos[1];

	//difficulty->visible = 1;
	//judgeRecord->visible = 1;
	//scoreRecord->visible = 1;
	addChild(difficulty);
	addChild(scoreRecord);
	addChild(judgeRecord);
}
void WindowMapLevel::initializeLevelCommands() {
	levelCommandGroup = new SpriteCommandGroup(menuCommandBg, 2, 0);
	SpriteCommand* cmd;

	levelCommandGroup->z = 50;
	levelCommandGroup->x = LevelSelectPos[0];
	levelCommandGroup->y = LevelSelectPos[1];

	cmd = levelCommandGroup->addCommand(Bitmap::getBitmap("LevelCommand1.txt"));
	cmd->x = 0; cmd->y = 0;
	cmd = levelCommandGroup->addCommand(Bitmap::getBitmap("LevelCommand2.txt"));
	cmd->x = 0; cmd->y = 20;
	cmd = levelCommandGroup->addCommand(Bitmap::getBitmap("LevelCommand3.txt"));
	cmd->x = 256; cmd->y = 0;
	cmd = levelCommandGroup->addCommand(Bitmap::getBitmap("LevelCommand4.txt"));
	cmd->x = 256; cmd->y = 20;

	//levelCommandGroup->setActiveShake(false);
	//levelCommandGroup->setActiveShineChar('*');
	//levelCommandGroup->deactivate();
	levelCommandGroup->visible = 1;
	addChild(levelCommandGroup);
}
void WindowMapLevel::initializeMapPic() {
	mapPic = new Sprite();
	mapPic->x = MapPicPos[0];
	mapPic->y = MapPicPos[1];

	mapNames = new Sprite();

	addChild(mapPic);
	addChild(mapNames);
}
void WindowMapLevel::activate() {
	//SpriteWindow::activate(); levelCommandGroup->activate(); visible = true;
}
void WindowMapLevel::deactivate() {
	//SpriteWindow::deactivate(); levelCommandGroup->deactivate(); visible = false;
}

void WindowMapLevel::refresh() {
	SpriteWindow::refresh();
	refreshMapInfo();
	refreshMapPic();
}
void WindowMapLevel::refreshMapInfo() {
	
}

void WindowMapLevel::refreshMapPic() {
	int index = map->index;
	mapPic->setBitmap(Bitmap::getBitmap(WindowMap::MapPicFiles[index][0]));

	mapNames->setBitmap(Bitmap::getBitmap(WindowMap::MapPicFiles[index][1]));
	mapNames->x = mapPic->x;
	mapNames->y = mapPic->y + mapPic->getSpriteHeight() -
		mapNames->getSpriteHeight();
}

void WindowMapLevel::processOK() {
	SpriteWindow::processOK();
	SpriteWindow::processBack();
	//ScreenManager::pushScene(new SceneBattle(map->index, levelCommandGroup->getIndex()));
}

void WindowMapLevel::updateOthers() {
	SpriteWindow::updateOthers();
	updateControl();
}
void WindowMapLevel::updateControl() {
	SpriteWindow::updateControl();
	//if (levelCommandGroup->isIndexChanged()) refreshMapInfo();
}





WindowBattleResult::WindowBattleResult() :
	SpriteWindow(Bitmap::getBitmap("BattleResultWindow.txt")) {
	initialize();
}
WindowBattleResult::~WindowBattleResult() {
	delete timeNeed, recoverPoint;
	delete beHurtPoint, hurtPoint;
	delete difficulty, finalScore;
	delete goldGain, judge;
}
void WindowBattleResult::initialize() {
	SpriteWindow::initialize();
	popScene = setuped = false;
	initializeParams();
}
void WindowBattleResult::initializeParams() {
	
}

void WindowBattleResult::setup() {
	setuped = true; duration = 0;
	//gold = BattleManager::getGold();
	refresh();
}
void WindowBattleResult::refresh() {
	SpriteWindow::refresh();
	refreshParams();
}
void WindowBattleResult::refreshParams() {
	char diff[10];
	
	difficulty->setText(diff);
	
}
void WindowBattleResult::requestPopScene() { popScene = true; }
void WindowBattleResult::processOK() { requestPopScene(); }
void WindowBattleResult::processBack() { requestPopScene(); }

bool WindowBattleResult::popSceneRequest() { return popScene; }


void WindowBattleResult::updateOthers() {
	SpriteWindow::updateOthers();
	if (setuped) updateTextAni();
}
void WindowBattleResult::updateTextAni() {
	duration++;
	updateGoldAni();
	updateJudgeAni();
}
void WindowBattleResult::updateGoldAni() {
	
}
void WindowBattleResult::updateJudgeAni() {
	if (duration > GoldTextAniDuration && duration <= 1.5 * GoldTextAniDuration) {
		
	}
}


WindowShop::WindowShop() :SpriteWindow(menuShopBackground) {

	initialize(); //setup(); setMap(NULL); //refresh();
}
void WindowShop::initialize() {
	SpriteWindow::initialize();
	initializegoods();
	
}
void WindowShop::initializegoods() {
	goodsGroup = new SpriteCommandGroup(menuCommandBg, 2, 0);//***********************

	SpriteCommand* cmd;

	goodsGroup->z = 50;
	goodsGroup->x = GoodBlockPos[0];
	goodsGroup->y = GoodBlockPos[1];
//刀 只有这样排序才能成功
	cmd = goodsGroup->addCommand(Bitmap::getBitmap("weapon1.txt"));//1
	cmd->x = 0; cmd->y = 0;
	cmd->howmuch = 600;
	cmd = goodsGroup->addCommand(Bitmap::getBitmap("weapon3.txt"));//3
	cmd->x = 0; cmd->y = 40;
	cmd->howmuch = 3000;
	cmd = goodsGroup->addCommand(Bitmap::getBitmap("weapon4.txt"));//4
	cmd->x = 0; cmd->y = 60;
	cmd->howmuch = 6300;
	cmd = goodsGroup->addCommand(Bitmap::getBitmap("weapon5.txt"));//5
	cmd->x = 0; cmd->y = 80;
	cmd->howmuch = 7800;
	cmd = goodsGroup->addCommand(Bitmap::getBitmap("weapon6.txt"));//6
	cmd->x = 0; cmd->y = 100;
	cmd->howmuch = 12000;
	cmd = goodsGroup->addCommand(Bitmap::getBitmap("weapon2.txt"));//2
	cmd->x = 0; cmd->y = 20;
	cmd->howmuch = 1800;


	
	goodsGroup->visible = 1;
	addChild(goodsGroup);
}