#pragma once

#include "Sprite.h"
class Sprite;
class SpriteVarBar : public Sprite {
public:
	static const int MoveSpeed;

	SpriteVarBar(string barName, string backgroundName);
	SpriteVarBar(Bitmap* barBitmap, Bitmap* backgroundBitmap);
	~SpriteVarBar();

	void setRate(double r, bool setup = false);
	double getRate();
	bool displayEnd();

	int getWidth();
	int getHeight();

private:
	double rate, targetRate;
	Sprite* background;
protected:
	void updateOthers();
	void updateRate();
	void updateFrame();
};
