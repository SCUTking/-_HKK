#include"stdafx.h"
#include"Spritecmd.h"
#include"Database.h"
#include"key.h"


SpriteCommand::SpriteCommand() :Sprite() {}

SpriteCommand::SpriteCommand(Bitmap* background, int aniId, bool type) {
	this->SpriteCommand::SpriteCommand(background, &animations[aniId], type);
}
SpriteCommand::SpriteCommand(Bitmap* background, AnimationData* data, bool type) :
	Sprite(background) {
	setSelectedAni(data); //setupContents(type, new Bitmap());
}

SpriteCommand::SpriteCommand(Bitmap* background, int aniId, Bitmap* fontFace, string txt) {
	this->SpriteCommand::SpriteCommand(background, &animations[aniId], fontFace, txt);
}
SpriteCommand::SpriteCommand(Bitmap* background, AnimationData* data, Bitmap* fontFace, string txt) {
	this->SpriteCommand::SpriteCommand(background, new Animation(data), fontFace, txt);
}
SpriteCommand::SpriteCommand(Bitmap* background, Animation* ani, Bitmap* fontFace, string txt) :
	Sprite(background) {
	//initSprites();
	//setupContents(false, fontFace);
	setSelectedAni(ani); 
	//setText(txt);
}

SpriteCommand::SpriteCommand(Bitmap* background, int aniId, Bitmap* img) {
	this->SpriteCommand::SpriteCommand(background, &animations[aniId], img);


	
}
SpriteCommand::SpriteCommand(Bitmap* background, AnimationData* data, Bitmap* img) {
	this->SpriteCommand::SpriteCommand(background, new Animation(data), img);
}

SpriteCommand::SpriteCommand(Bitmap* background, Animation* ani, Bitmap* img) :
	Sprite(background) {
	//initSprites();
	//setupContents(true, img);
	setSelectedAni(ani);



	//Ìî³ädata2
	this->visible = 1;
	this->resource = img;
	this->pictureheigth = this->resource->height;
	this->picturewidth = this->resource->width;
	createdata();
	wholewritedata2();
}



void SpriteCommand::activate() {
	selectedAniSprite->play();
}
void SpriteCommand::deactivate() {
	selectedAniSprite->pause();
}
bool SpriteCommand::isSelected() { return selected; }

void SpriteCommand::setActiveShine(bool val) { activeShine = val; }
void SpriteCommand::setActiveShineChar(char c) { activeShineChar = c; }
void SpriteCommand::setActiveShake(bool val) { activeShake = val; }

bool SpriteCommand::getActiveShine() { return activeShine; }
bool SpriteCommand::getActiveShake() { return activeShake; }

void SpriteCommand::clearSelectedAni() { setSelectedAni(NULL); }
void SpriteCommand::setSelectedAni(int aniId) { setSelectedAni(&animations[aniId]); }
void SpriteCommand::setSelectedAni(AnimationData* data) { setSelectedAni(new Animation(data)); }
void SpriteCommand::setSelectedAni(Animation* ani) {//Í¼±ê
	if (selectedAniSprite != NULL)
		removeChild(selectedAniSprite);
	selectedAniSprite = ani;
	if (ani == NULL) return;
	selectedAniSprite->setLoop(true);
	selectedAniSprite->z = -5;
	//selectedAniSprite->stop();
	selectedAniSprite->visible = false;
	addChild(selectedAniSprite);//Ìí¼Ó¶ù×Ó
}















SpriteCommandGroup::SpriteCommandGroup(Bitmap* background, int aniId, int firstSelect) {
	this->SpriteCommandGroup::SpriteCommandGroup(background, NULL, &animations[aniId], firstSelect);
}
SpriteCommandGroup::SpriteCommandGroup(Bitmap* background, Bitmap* fontFace, int aniId, int firstSelect) {
	this->SpriteCommandGroup::SpriteCommandGroup(background, &animations[aniId], firstSelect);

}
SpriteCommandGroup::SpriteCommandGroup(Bitmap* background, AnimationData* data, int firstSelect) {
	this->SpriteCommandGroup::SpriteCommandGroup(background, NULL, data, firstSelect);
}
SpriteCommandGroup::SpriteCommandGroup(Bitmap* background, Bitmap* fontFace, AnimationData* data, int firstSelect) {
	keyCd = 0;
	selectedAniData = data;
	selectedAni = new Animation(data);
	//this->background = background;
	this->fontFace = fontFace;
	this->firstSelect = firstSelect;
}

//SpriteCommandGroup::~SpriteCommandGroup() { clearCommands(); }

SpriteCommand* SpriteCommandGroup::addCommand(string txt) {
	return addCommand(txt, fontFace);
}
SpriteCommand* SpriteCommandGroup::addCommand(string txt, Bitmap* fontFace) {
	if (fontFace != NULL) return addCommand(new SpriteCommand(background, selectedAniData, fontFace, txt));
	return NULL;
}
SpriteCommand* SpriteCommandGroup::addCommand(Bitmap* img) {

	return addCommand(new SpriteCommand(background,selectedAniData,img));
}
SpriteCommand* SpriteCommandGroup::addCommand(SpriteCommand* command) {
	commands.push_back(command);
	addChild(command);
	//select(firstSelect);
	return command;
}




