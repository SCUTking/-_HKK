#pragma once
#include<string>
#include<vector>
#include"Bitmap.h"
#include<algorithm>
#include"rect.h"
using namespace std;
class DisplayObject;





extern Bitmap* titleCommand1;
extern Bitmap* titleCommand2;
extern Bitmap* titleCommand3;

extern Bitmap* titleCommandBg;
extern Bitmap* Background3;
extern Bitmap* menuBackground;
extern Bitmap* menuMapBackground;
extern Bitmap* menuMapLevelBackground;
extern Bitmap* menuItemBackground;
extern Bitmap* menuSkillBackground;
extern Bitmap* menuShopBackground;
extern Bitmap* menuSaveBackground;

extern Bitmap* menuCommandBg;
extern Bitmap* menuItemCommandBg;
extern Bitmap* menuEquipCommandBg;
extern Bitmap* menuSkillCommandBg;
extern Bitmap* menuFileCommandBg;

extern Bitmap* defaultFontFaceSmall;
extern Bitmap* defaultFontFace;
extern int defaultFontYCount;
extern Bitmap* damageFontFace;

extern Bitmap* weaponBitmap;

extern Bitmap* hpDisplayBar;
extern Bitmap* hpDisplayBg;

extern Bitmap* hpBarBitmap;
extern Bitmap* mpBarBitmap;

extern Bitmap* battleHpBarBitmap;
extern Bitmap* battleMpBarBitmap;

extern Bitmap* battleStateUI;
extern Bitmap* battleSlotsUI;






//cpp文件要用到的东西
void initDatabase();
void initSystem();
void initAnimations();
void initbattle();
void inittext();


struct System {
	static const int IconSetXCount = 16;
	static const int IconSetYCount = 33;
	static const int BaseParamCount = 8;
	static const int SpecialParamCount = 3;
	static const int EquipCount = 7;
	static const int MaxMapCount = 4;
	static const int MaxLevelCount = 4;
	static const int LevelPassReward[MaxLevelCount];
	static enum ItemType {
		Normal, LevelBall, Collection
	};
	static enum EquipType {
		Weapon, Helmet, Suit, Shoe, Earbob, Ring, Others
	};
	static enum WeaponType {
		Knife, Sword, Hammer, Axe, Whip, Staff
	};
	static enum ArmorType {
		Commonly
	};
	static enum SkillType {
		Physics, Magic
	};

	static enum OccasionType {
		NoneOccasion, Menu, Battle, Any
	};
	static enum TargetType {
		NoneTarget, Self, Friends, DeadFriends, Enemies
	};


};

struct BattleField {
	string fileName;
	string passableFileName;
	int playerCreatePos[2];
	Rect enemyCreateBlock;
	BattleField(string fn, string pfn);
};
struct BattleEnemy {
	int enemyId;
	int count = 1;
	Rect position;
	BattleEnemy(int id, int count, Rect position);
};
struct OperatorData {
	enum OperatorType {
		Freeze, Unfreeze, // 冻结&解冻
		ChangeDir, FixedDir, AutoDir, // 更改/固定/自动朝向
		SetVisible, // 设置 visible
		ForceMove, // 设置强制可移动性
		Move, MoveTo, // 移动/移动到 参数同 ObjectBattler 里
		MoveForward, MoveBackward,  // 向前向后移动
		MoveLeftward, MoveRightward,  // 向左向右移动
		MoveToTarget, // 移动到目标（第一个）
		Transfer, TransferTo, // 传送
		TransferForward, TransferBackward,  // 向前向后移动
		TransferLeftward, TransferRightward,  // 向左向右移动
		TransferToTarget, // 传送到目标
		Jump, ClearJump, // 跳跃：height, duration
		ChangeZ, // 更改Z坐标：z, duration
		ChangeSpeed, ResetSpeed, // 改变/复位速度
		Shake, ScreenShake, // 震动：power, duration
		Shine, ScreenShine, // 闪烁：char, duration
		SubSprite, // 分身：count, duration
		PlayAnimation, // 播放动画：id
		PlayAnimationAtTarget, // 目标播放动画：id

		ChangeMotion, // 姿态切换：motion, duration(-1: once)
		Wait, Delay, // 等待/硬直：duration
		Damage // 造成伤害：%
	};
	int timing;
	OperatorType oType;
	vector<int> params;
	OperatorData(int t, OperatorType type);
	OperatorData(int t, OperatorType type, vector<int> p);
	bool operator<(const OperatorData od) const;
	bool operator==(const OperatorData od) const;
};
struct SkillRange {
	bool wholeScreen = false; // 全屏敌人
	bool wholeLine = false;   // 全行敌人
	bool ballRange = false;	  // 球形范围
	bool fullAngle = false;   // 圆形范围（true->圆形，false->半圆）

	int pos[2] = { 0,0 }; // 位置指定（相对，朝向向左）

	int dist = 100;
	int count = -1;
	int zRange = 10;
};
struct AnimationData {//闪烁，攻击特效的数据
	static int BeingHurtAnimationId;
	static int count;
	int index;

	string name;

	int maxFrame;
	int xCount, yCount;
	int speed;

	//vector<ShineData> shine;

	string fileName;

	AnimationData(); // 必须
	AnimationData(string key, string file, int fc, int xc, int yc, int spd = 1);

	void addShineData(int time, int last, char c, bool screen = false);
	//void addShineData(ShineData dt);
};

struct Battler {
	int index;
	string name;
	string fileName;

	//vector<Skill*> learnedSkills;

	// MHP MMP ATK DEF MAT MDF AGI LUK
	int params[8] = { 100,10,1,1,1,1,1,1 };
	double specialParams[3] = { 0.8,0.05,0 };

	//void addSkill(int id);
	//void addSkill(Skill* skill);
	Battler(int id, string n, string fn);
};
struct Actor : Battler {
	static int count;
	string bigFace;
	double paramsGrowth[8] = { 0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1 };
	//vector<EquipSlot> initEquips;

	Actor(string n, string fn, string bf);
};
struct Enemy : Battler {
	enum AIType {
		None, // no attack, no move
		Closer, // attack range, close range, out of range move(stop/random)
		Idle, // attack range
		Random, // attack range,
		Loop // attack range, deltaX, deltaY
	};
	static int count;
	int level;
	int gold;

	AIType aiType = Random;
	vector<int> aiParams;

	int normalAttackRate = 5;
	vector<int> skillRate;

	//void addSkill(int id, int rate);
	//void addSkill(Skill* skill, int rate);
	Enemy(string n, string fn, int gold);
};

struct ItemBase {
	const int type = -1;
	int index = -1;
	string name = "";
	string fileName = "";
	int iconId = -1;
	int price = 0;
	ItemBase(int type, int id, string n = "", string fn = "", int ic = 0);
};
struct UsableItem : ItemBase {
	System::OccasionType occasion = System::OccasionType::Any;
	System::TargetType target = System::TargetType::Enemies;
	//vector<UsingEffect> usingEffects;                                    自己注释掉了

	int coolDown = 10, delay = 10;
	UsableItem(int type, int id, string n = "", string fn = "", int ic = 0, int cd = 10, int dl = 10);
	
};
struct Item : UsableItem {
	static int count;
	int usingAnimationId;
	bool consumable = true;
	System::ItemType iType;
	int minLevel = 0; int maxLevel = 100;
	Item(string n, string fn, int ic, int cd = 10, int dl = 2, System::ItemType type = System::ItemType::Normal);
};

struct Equip :ItemBase {
	System::EquipType eType;

	int params[System::BaseParamCount] = { 0,0,0,0,0,0 };
	double specialParams[System::SpecialParamCount] = { 0,0,0 };
	Equip(int type, int id, string n, string fn, int ic, System::EquipType eType);
};
struct Weapon : Equip {
	static int count;
	System::WeaponType wType;
	Weapon(string n, string fn, int ic, System::WeaponType type);
};
struct Armor : Equip {
	static int count;
	System::ArmorType aType;
	Armor(string n, string fn, int ic, System::EquipType etype,
		System::ArmorType atype = System::ArmorType::Commonly);
};
struct Skill : UsableItem {
	static int count;
	int mpCost = 0;
	int learnedLevel = 0;
	SkillRange range; // x,y,z
	vector<System::WeaponType> weaponRequirements;
	vector<OperatorData> preSkillOper;
	vector<OperatorData> usingOper;
	vector<OperatorData> targetOper;
	System::SkillType sType; // 0 -> 必杀技   1 -> 魔法
	Skill(string n, string fn, int ic, int cost, int cd = 10, int dl = 10,
		System::SkillType type = System::SkillType::Physics);

	OperatorData* addPreSkillOper(int timing, OperatorData::OperatorType type);
	OperatorData* addUsingOper(int timing, OperatorData::OperatorType type);
	OperatorData* addTargetOper(int timing, OperatorData::OperatorType type);
};
struct Shop {
	string name;
	vector<ItemBase*> list;
	void addSellItem(ItemBase* item);
	Shop(string name);
};

struct Battle {
	static int count;
	int index = -1;
	string name = "";
	double difficluty = 1;
	BattleField battleField;
	vector<BattleEnemy> battleEnemies;

	void addEnemy(int id, int cnt, Rect pos);
	void addEnemy(Enemy* enemy, int cnt, Rect pos);
	Battle(string n, string bfn, string bfpn, double difficluty = 1);
};

void initActors();

//需要的一些vector,定义要在后面
extern vector<Actor> actors;
extern vector<AnimationData> animations;
extern vector<Enemy> enemies;

extern vector<Item> items;
extern vector<Weapon> weapons;
extern vector<Armor> armors;
extern vector<Skill> skills;

extern vector<Shop> shops;

extern vector<Bitmap*> battles;//自己写的

extern vector<OperatorData> normalTargetOper;
extern vector<OperatorData> criticalOper;
extern vector<OperatorData> missOper;
extern vector<DisplayObject*> texts;