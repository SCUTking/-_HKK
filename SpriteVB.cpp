#include "stdafx.h"
#include "SpriteVB.h"
const int SpriteVarBar::MoveSpeed = 5;

SpriteVarBar::SpriteVarBar(string barName, string backgroundName) {
	this->SpriteVarBar::SpriteVarBar(Bitmap::getBitmap(barName), Bitmap::getBitmap(backgroundName));
}
SpriteVarBar::SpriteVarBar(Bitmap* barBitmap, Bitmap* backgroundBitmap) : Sprite(barBitmap) {
	background = new Sprite(backgroundBitmap);
	addBackChild(background);
	setRate(1, true);
	visible = false;
}
SpriteVarBar::~SpriteVarBar() {
	delete background;
}

int SpriteVarBar::getWidth() { return background->getSpriteWidth(); }
int SpriteVarBar::getHeight() { return background->getSpriteHeight(); }

void SpriteVarBar::setRate(double r, bool setup) {
	targetRate = r;
	if (setup) rate = r;
}
double SpriteVarBar::getRate() { return targetRate; }

bool SpriteVarBar::displayEnd() { return abs(targetRate - rate) <= 0.0001; }

void SpriteVarBar::updateOthers() {
	//Sprite::updateOthers();
	updateRate();
}
void SpriteVarBar::updateRate() {
	if (!displayEnd()) {
		rate += (targetRate - rate) / MoveSpeed;
		updateFrame();
	}
	else rate = targetRate;
}
void SpriteVarBar::updateFrame() {
	setFrameRect(0, 0, picturewidth * rate, pictureheigth);
}