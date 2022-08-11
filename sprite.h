#pragma once
using namespace std;
//sprite,”Îspritecommand√ª”–data2
#include"Bitmap.h"
#include"DisplayObject.h"

struct Rect;
class DisplayObject;
class Sprite : public DisplayObject {
public:
	Sprite();
	Sprite(string fileName);
	Sprite(Bitmap* bitmap);
	

    
	void quickRender(char**& map, int lx, int ly);

	void setBitmap(Bitmap* bitmap);
	Bitmap* getBitmap();
	void setFrameRect(Rect rect);
	void setFrameRect(int x, int y, int width, int height);
	

	
	int getSpriteWidth() const;
	int getSpriteHeight() const;

	

protected:

	int rx, ry;
	int count;
	char shineChar;
	int shakePower;
	bool shakeY;
	double shakeSpeed;
	int shineDuration;
	int shakeDuration;
	bool shineTransparent;
	bool mirror;
	//Bitmap* bitmap;
	Rect frameRect;
};


class Animation : public Sprite {
public:
	Animation(int id);
	Animation(AnimationData* data);

	void start(); void play(); void pause(); //void stop();
	void setSpeed(int spd);
	int getSpeed();
	void setLoop(bool l);
	void setReverse(bool r);

	void setAutoRotate(bool r);
	bool isAutoRotate();

	int duration();
	bool isPlaying();
	bool isEnded();

	int getFrameRectWidth();
	int getFrameRectHeight();

private:
	int getFrameRectX();
	int getFrameRectY();

	//void makeShineData();

	int count, frame;
	int speed;
	int lastFrame;

	bool playing;
	bool loop;
	bool reverse;
	bool autoRotate;
	AnimationData* aData;

	//vector<ShineData*> shineData;
protected:


	int animationFunction(int c);
};

class SpriteExtend : public Sprite {
public:
	SpriteExtend();
	SpriteExtend(string fileName);
	SpriteExtend(Bitmap* bitmap);
	SpriteExtend(int width, int height);

	virtual void addAnimation(Animation ani);
	virtual void addAnimation(AnimationData* ani);
	virtual void addAnimation(Animation* ani);

	virtual void removeAnimation(Animation ani);
	virtual void removeAnimation(Animation* ani);

	Animation* getAnimation(int id);

	virtual void setMirror(bool mir);

protected:
	virtual void updateOthers();
	virtual void updateAnimations();

	vector<Animation*> animations;
};