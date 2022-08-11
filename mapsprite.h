#pragma once

#include"Sprite.h"
//#include"ObjectBattler.h"
//#include"SpriteBattler.h"
struct BattleField;

class SpriteMap : public Sprite {
public:
	SpriteMap(BattleField* battleField);

	//void addBattler(SpriteBattler* battler);
	//void removeBattler(SpriteBattler* battler);
private:
	void updateOthers();
	void updateBattlers();
	void updateScroll();

	//vector<SpriteBattler*> battlers;

	BattleField* battleField;
	//ObjectActor* actor;

};
bool BattlerZComp(const DisplayObject* a, const DisplayObject* b);
