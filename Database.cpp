#include"stdafx.h"
#include"Database.h"
#include"screenManager.h"
#include<vector>


Bitmap* titleCommand1;
Bitmap* titleCommand2;
Bitmap* titleCommand3;

Bitmap* titleCommandBg;
Bitmap* defaultFontFaceSmall;
Bitmap* defaultFontFace;


Bitmap* Background3;
Bitmap* menuBackground;
Bitmap* menuMapBackground;
Bitmap* menuMapLevelBackground;
Bitmap* menuItemBackground;
Bitmap* menuSkillBackground;
Bitmap* menuShopBackground;
Bitmap* menuSaveBackground;

Bitmap* menuCommandBg;
Bitmap* menuItemCommandBg;
Bitmap* menuEquipCommandBg;
Bitmap* menuSkillCommandBg;
Bitmap* menuFileCommandBg;

int defaultFontYCount = 8;

vector<AnimationData> animations;
vector<Actor> actors;
vector<Enemy> enemies;

vector<Item> items;
vector<Weapon> weapons;
vector<Armor> armors;
vector<Skill> skills;

vector<Shop> shops;

vector<Bitmap*> battles;

vector<OperatorData> normalTargetOper;
vector<OperatorData> criticalOper;
vector<OperatorData> missOper;
vector<DisplayObject*> texts;//自己写的


int AnimationData::count = 0;//结构体中静态成员的定义
int Actor::count = 0;
 
 void initDatabase() {
	 initSystem();
	 initAnimations();
	 initActors();
	 initbattle();
	 inittext();
 }
 void initAnimations() {


animations.push_back(AnimationData("NormalHurt", "../HKK/ASCII-Stick.txt", 8, 5, 2, 2));
 animations.push_back(AnimationData("TitleSelectorAni", "TitleSelectorAni.txt", 4, 1, 4, 3));
 animations.push_back(AnimationData("MenuSelectorAni", "MenuSelectorAni.txt", 6, 1, 6, 2));
 animations.push_back(AnimationData("MenuItemSelectorAni", "ItemFrameSelectAni.txt", 4, 1, 4, 3));
 animations.push_back(AnimationData("MenuEquipSelectorAni", "EquipFrameSelectAni.txt", 4, 1, 4, 3));
 animations.push_back(AnimationData("MenuSkillSelectorAni", "SkillFrameSelectAni.txt", 4, 1, 4, 3));


 animations.push_back(AnimationData("NormalHeal", "Heal.txt", 12, 5, 3, 2));
 animations.push_back(AnimationData("GroundHitAni", "GroundHitAni.txt", 8, 4, 2, 2));
 animations.push_back(AnimationData("HeavyHitAni", "HeavyHit.txt", 7, 5, 2, 2));

 animations.push_back(AnimationData("RotateHitAni", "RotateHit.txt", 8, 2, 4, 2));

 animations.push_back(AnimationData("FireCall", "FireCall.txt", 23, 5, 5, 2));
 animations.push_back(AnimationData("FireAttack", "FireAttack.txt", 12, 5, 3, 2));
 animations.push_back(AnimationData("Sprint", "Sprint.txt", 9, 1, 9, 2));
 animations.push_back(AnimationData("ElectricSprint", "ElectricSprint.txt", 4, 1, 4, 3));

 animations.push_back(AnimationData("MenuMapSelectorAni", "MapSelectAni.txt", 2, 1, 2, 3));
 animations.push_back(AnimationData("MenuFileSelectorAni", "FileFrameSelectAni.txt", 4, 1, 4, 3));

 animations.push_back(AnimationData("Wind", "Wind.txt", 13, 2, 7, 2));
 animations.push_back(AnimationData("Ares'sBiff", "Ares'sBiff.txt", 16, 5, 4, 2));
 animations.push_back(AnimationData("AbsorbKiri", "AbsorbKiri.txt", 5, 5, 1, 2));
 animations.push_back(AnimationData("EarthRoar", "EarthRoar.txt", 13, 5, 3, 1));
 animations.push_back(AnimationData("UpKiri", "UpKiri.txt", 9, 2, 5, 2));
 animations.push_back(AnimationData("SwordRain", "SwordRain.txt", 8, 2, 4, 3));
 animations.push_back(AnimationData("1000Kill", "1000Kill.txt", 8, 4, 2, 3));
 animations.push_back(AnimationData("FireSword", "FireSword.txt", 14, 5, 3, 1));
 animations.push_back(AnimationData("IceSword", "IceSword.txt", 14, 5, 3, 1));
 animations.push_back(AnimationData("ThunderSword", "ThunderSword.txt", 14, 5, 3, 1));
 animations.push_back(AnimationData("FireDash", "FireDash.txt", 6, 3, 2, 2));
 animations.push_back(AnimationData("Wind", "Wind.txt", 13, 2, 7, 3));
 animations.push_back(AnimationData("MagicGas", "MagicGas.txt", 3, 3, 1, 3));
 animations.push_back(AnimationData("IceAttack", "IceAttack.txt", 15, 5, 3, 1));
 animations.push_back(AnimationData("ThunderAttack", "ThunderAttack.txt", 7, 4, 2, 1));
 animations.push_back(AnimationData("IceLock", "IceLock.txt", 12, 4, 3, 1));
 animations.push_back(AnimationData("Water", "Water.txt", 19, 5, 4, 1));
 animations.push_back(AnimationData("RedFirePre", "RedFirePre.txt", 12, 5, 3, 1));
 animations.push_back(AnimationData("RedFire1", "RedFire1.txt", 15, 5, 3, 2));
 animations.push_back(AnimationData("RedFire2", "RedFire2.txt", 11, 5, 3, 1));
 animations.push_back(AnimationData("MagicZhin", "MagicZhin.txt", 20, 5, 4, 1));
 animations.push_back(AnimationData("BlackHole", "BlackHole.txt", 29, 5, 6, 1));
 animations.push_back(AnimationData("Special", "SpecialSkill.txt", 35, 7, 5, 2));
 animations.push_back(AnimationData("KiRinPre", "KiRinPre.txt", 12, 5, 3, 1));
 animations.push_back(AnimationData("KiRin", "KiRin.txt", 5, 5, 1, 1));
 animations.push_back(AnimationData("PreLight", "PreLight.txt", 25, 5, 5, 1));
 animations.push_back(AnimationData("Light", "Light.txt", 19, 5, 4, 2));
 }

 void initSystem()
 {
	
	 titleCommand1 = Bitmap::getBitmap("TitleCommand1.txt");
	 titleCommand2 = Bitmap::getBitmap("TitleCommand2.txt");
	 titleCommand3 = Bitmap::getBitmap("TitleCommand3.txt");
	 titleCommandBg = Bitmap::getBitmap("TitleCommandBg.txt");

	 defaultFontFace = Bitmap::getBitmap("NormalText.txt");
	 defaultFontFaceSmall = Bitmap::getBitmap("NormalText_small.txt");

	 menuBackground = Bitmap::getBitmap("MenuBackground.txt");
	 menuMapBackground = Bitmap::getBitmap("MenuMapBg.txt");
	 menuMapLevelBackground = Bitmap::getBitmap("MenuMapLevelBg.txt");
	 menuItemBackground = Bitmap::getBitmap("MenuItemBg.txt");

	 menuSkillBackground = Bitmap::getBitmap("MenuSkillBg.txt");
	 menuShopBackground = Bitmap::getBitmap("MenuShopBg.txt");
	 menuSaveBackground = Bitmap::getBitmap("MenuSaveBg.txt");

	 menuCommandBg = Bitmap::getBitmap("MenuCommandBg.txt");
	 menuItemCommandBg = Bitmap::getBitmap("ItemFrame.txt");
	 menuEquipCommandBg = Bitmap::getBitmap("EquipFrame.txt");
	 menuSkillCommandBg = Bitmap::getBitmap("SkillFrame.txt");
	 menuFileCommandBg = Bitmap::getBitmap("FileFrame.txt");


	 Background3 = Bitmap::getBitmap("Background.txt");

 }
 void initActors() {
	 Actor* actor;
		 int params[8] = { 625,100,15,8,5,6,8,10 };
		 double paramsGrowth[8] = { 0.12,0.08,0.14,0.11,0.03,0.08,0.09,0.09 };
		 actors.push_back(Actor("Poword", "Actor1_bt.txt", "Actor1_true.txt"));
		 actor = &actors[actors.size() - 1];
		 for (int i = 0; i < 8; i++) {
			 actor->params[i] = params[i];
			 actor->paramsGrowth[i] = paramsGrowth[i];
		 }
	 
	 
		 int params1[8] = { 520,375,6,4,18,10,6,7 };
		 double paramsGrowth1[8] = { 0.08,0.10,0.05,0.04,0.15,0.11,0.07,0.08 };
		 actors.push_back(Actor("Mogician", "Actor2_bt.txt", "女巫.txt"));
		 actor = &actors[actors.size() - 1];
		 for (int i = 0; i < 8; i++) {
			 actor->params[i] = params1[i];
			 actor->paramsGrowth[i] = paramsGrowth1[i];
		 }
	 
	 
		 int params2[8] = { 660,75,17,6,5,5,12,4 };
		 double paramsGrowth2[8] = { 0.11,0.07,0.13,0.08,0.04,0.07,0.10,0.06 };
		 actors.push_back(Actor("Werof", "Actor3_bt.txt", "Actor3_true.txt"));
		 actor = &actors[actors.size() - 1];
		 for (int i = 0; i < 8; i++) {
			 actor->params[i] = params2[i];
			 actor->paramsGrowth[i] = paramsGrowth2[i];
		 }
	 
	 
		 int params3[8] = { 580,300,14,7,13,6,9,4 };
		 double paramsGrowth3[8] = { 0.10,0.10,0.10,0.07,0.10,0.08,0.08,0.05 };
		 actors.push_back(Actor("Chivalry", "Actor4_bt.txt", "Actor4_true.txt"));
		 actor = &actors[actors.size() - 1];
		 for (int i = 0; i < 8; i++) {
			 actor->params[i] = params3[i];
			 actor->paramsGrowth[i] = paramsGrowth3[i];
		 }
	 
 }
 void initbattle() {
	 battles.push_back(Bitmap::getBitmap("Battle1.txt"));
	 battles.push_back(Bitmap::getBitmap("Battle2.txt"));
	 battles.push_back(Bitmap::getBitmap("Battle3_r.txt"));
	 battles.push_back(Bitmap::getBitmap("Battle4_r.txt"));
 }

 void inittext() {
	 int x = 9; int y = 9;//visible=1
	 DisplayObject* text;
	 text = new DisplayObject(x, y, 168, 132, Bitmap::getBitmap("text1.txt"));
	 text->wholewritedata2();
	 texts.push_back(text);
	 text = new DisplayObject(x, y, 168, 132, Bitmap::getBitmap("text2.txt"));
	 text->wholewritedata2();
	 texts.push_back(text);
	 text = new DisplayObject(x, y, 168, 132, Bitmap::getBitmap("text4.txt"));
	 text->wholewritedata2();
	 texts.push_back(text);
	 text = new DisplayObject(x, y, 168, 132, Bitmap::getBitmap("text3.txt"));
	 text->wholewritedata2();
	 texts.push_back(text);
	
 }








AnimationData::AnimationData() {};
AnimationData::AnimationData(string key, string file, int fc, int xc, int yc, int spd) :
	index(AnimationData::count++), name(key), fileName(file), maxFrame(fc), xCount(xc), yCount(yc), speed(spd) {}

void AnimationData::addShineData(int time, int last, char c, bool screen) {
	////addShineData(ShineData(time, last, c, screen));
}




Battler::Battler(int id, string n, string fn) : index(id), name(n), fileName(fn) {}
Actor::Actor(string n, string fn, string bf) : Battler(Actor::count++, n, fn), bigFace(bf) {
	//for (int i = 0; i < System::EquipCount; i++)
		//initEquips.push_back(EquipSlot(System::EquipType(i)));
}