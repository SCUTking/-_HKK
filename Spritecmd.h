#pragma once
#include"sprite.h"
#include"testplay.h"
class Sprite;
class Animation;
class SpriteCommand : public Sprite {
public:
	SpriteCommand();

	SpriteCommand(Bitmap* background, int aniId, bool type = false);
	SpriteCommand(Bitmap* background, AnimationData* data, bool type = false);

	SpriteCommand(Bitmap* background, int aniId, Bitmap* fontFace, string txt);
	SpriteCommand(Bitmap* background, AnimationData* data, Bitmap* fontFace, string txt);
	SpriteCommand(Bitmap* background, Animation* ani, Bitmap* fontFace, string txt);

	SpriteCommand(Bitmap* background, int aniId, Bitmap* img);
	SpriteCommand(Bitmap* background, AnimationData* data, Bitmap* img);
	SpriteCommand(Bitmap* background, Animation* ani, Bitmap* img);





	
	void activate(); void deactivate();
	bool isSelected();




	void setActiveShine(bool val);
	void setActiveShake(bool val);
	void setActiveShineChar(char c);

	bool getActiveShine();
	bool getActiveShake();

	void clearSelectedAni();
	void setSelectedAni(int aniId);
	void setSelectedAni(AnimationData* data);
	void setSelectedAni(Animation* ani);
private:
	bool imgCommand;

	bool selected;

	bool activeShine;
	char activeShineChar;
	bool activeShake;

	Animation* selectedAniSprite;
	//TextDisplay* textDisplay;
	Sprite* textSprite;
	Sprite* contentSprite;
};

class SpriteCommandGroup : public Sprite {
public:
	int index;


	SpriteCommandGroup(Bitmap* background, int aniId, int firstSelect = 0);
	SpriteCommandGroup(Bitmap* background, Bitmap* fontFace, int aniId, int firstSelect = 0);
	SpriteCommandGroup(Bitmap* background, AnimationData* data, int firstSelect = 0);
	SpriteCommandGroup(Bitmap* background, Bitmap* fontFace, AnimationData* data, int firstSelect = 0);
	
	//~SpriteCommandGroup();

	SpriteCommand* addCommand(string txt);
	SpriteCommand* addCommand(string txt, Bitmap* fontFace);
	SpriteCommand* addCommand(Bitmap* img);
	SpriteCommand* addCommand(SpriteCommand* command);
	

	
	


private:


	int keyCd;
	bool active;
	bool loop;

	bool indexChanged;

	int firstSelect;

	Bitmap* background;
	Bitmap* fontFace;
	Animation* selectedAni;
	AnimationData* selectedAniData;
	vector<SpriteCommand*> commands;
protected:


};