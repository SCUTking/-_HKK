#include"stdafx.h"
#include"sprite.h"
#include"DisplayObject.h"
void Sprite::setBitmap(Bitmap* bitmap) {
	
	this->resource = bitmap;
	setall(); //更新data2
	//initialiazeFrameRect();
}

int Sprite::getSpriteWidth() const { return frameRect.width; }
int Sprite::getSpriteHeight() const { return frameRect.height; }
Bitmap* Sprite::getBitmap() { return resource; }
//int Sprite::getSpriteWidth() const { return frameRect.width; }
//int Sprite::getSpriteHeight() const { return frameRect.height; }

Sprite::Sprite() {
	this->Sprite::Sprite(new Bitmap());
}
Sprite::Sprite(string fileName) {
	
	this->Sprite::Sprite(Bitmap::getBitmap(fileName));
}
/*Sprite::Sprite(int width, int height) {
	this->Sprite::Sprite(new Bitmap(width, height));
}*/
Sprite::Sprite(Bitmap* bitmap) {
	
	setBitmap(bitmap);
	//initialiaze();
}
void Sprite::setFrameRect(int x, int y, int width, int height) {
	setFrameRect(Rect(x, y, width, height));
}
void Sprite::setFrameRect(Rect rect) {
	frameRect = rect;
}



void Sprite::quickRender(char**& map, int lx, int ly) {
	if (!visible) return;
	
	// 渲染后面的内容
	for (int i = 0; i < backChildren.size(); i++) {
		DisplayObject* obj = backChildren[i];
		int ox = obj->x; int oy = obj->y;
		obj->quickRender(map, lx + ox, ly + oy);
	}

	// 执行渲染，首先获取Sprite上的Bitmap中的渲染数据（字符数据）
	char** data = this->resource->data1;
	int width = this->resource->width;
	int height = this->resource->height;

	// frameRect 为当前Sprite所占的空间矩形
	/*for (int y = 0; y < frameRect.height; y++) {
		for (int x = 0; x < frameRect.width; x++) {
			int dx = x + frameRect.x; int dy = y + frameRect.y;
			if (mirror) // 处理镜像
				dx = frameRect.x + frameRect.width - x;

			int sx = x + lx; int sy = y + ly;
			if (dy >= 0 && dy < height && dx >= 0 && dx < width &&
				sy >= 0 && sy < GHeight && sx >= 0 && sx < GWidth)
				// 处理透明情况，T代表透明
				if (data[dy][dx] != 'T') map[sy][sx] =
					(shineDuration > 0 || shineDuration == -1) ? shineChar : data[dy][dx];
				else if ((shineDuration > 0 || shineDuration == -1) && shineTransparent)
					map[sy][sx] = shineChar; // 处理闪烁效果
		}
	}*/

	// 渲染前面的内容
	for (int i = 0; i < children.size(); i++) {
		DisplayObject* obj = children[i];
		int ox = obj->x; int oy = obj->y;
		obj->quickRender(map, lx + ox, ly + oy);
	}
}





Animation::Animation(int id) {
	this->Animation::Animation(&animations[id]);
}
// Sprite(data->fileName)
// 读取的是对应文件的Bitmap
Animation::Animation(AnimationData* data) :Sprite(data->fileName) {
	count = frame = 0;
	aData = data; // 动画数据
	//makeShineData(); // 设置闪烁效果
	setSpeed(data->speed); // 设置播放速度
	picturewidth = this->resource->width;
	pictureheigth = this->resource->height;
	//updateFrameRect();
	setAutoRotate(true);
	setReverse(false);
	setLoop(false);
	play();
}
/*
void Animation::makeShineData() {
	for (int i = 0; i < aData->maxFrame; i++) {
		shineData.push_back(NULL);
	}
	for (int i = 0; i < aData->shine.size(); i++) {
		shineData[aData->shine[i].time] = &aData->shine[i];
	}
}*/
void Animation::setSpeed(int spd) { speed = spd; }
int Animation::getSpeed() { return speed; }

void Animation::start() {
	count = frame = 0; playing = true;
}
void Animation::play() { playing = true; }
void Animation::pause() { playing = false; }
/*
void Animation::stop() {
	count = 0; frame = -1; playing = false;
	setFrameRect(Rect(0, 0, 0, 0));
}*/

void Animation::setLoop(bool l) { loop = l; }
void Animation::setReverse(bool r) { reverse = r; }

void Animation::setAutoRotate(bool r) { autoRotate = r; }
bool Animation::isAutoRotate() { return autoRotate; }

bool Animation::isPlaying() { return playing; }
bool Animation::isEnded() { return frame == -1; }


int Animation::getFrameRectX() {
	// 计算每一帧的X坐标
	return (frame % aData->xCount) * getFrameRectWidth();
}
int Animation::getFrameRectY() {
	// 计算每一帧的Y坐标
	return (frame / aData->xCount) * getFrameRectHeight();
}
int Animation::getFrameRectWidth() {
	// 计算每一帧的宽度
	return picturewidth / aData->xCount;
}
int Animation::getFrameRectHeight() {
	// 计算每一帧的高度
	return pictureheigth/ aData->yCount;
}
int Animation::duration() {
	// 总时长
	return aData->maxFrame * speed;
}




int Animation::animationFunction(int c) {
	return abs(c) / speed;
}


SpriteExtend::SpriteExtend() :Sprite() {}
SpriteExtend::SpriteExtend(string fileName) : Sprite(fileName) {}
SpriteExtend::SpriteExtend(int width, int height){} //: Sprite(width, height) //***************
SpriteExtend::SpriteExtend(Bitmap* bitmap) : Sprite(bitmap) {}

void SpriteExtend::addAnimation(AnimationData* ani) { addAnimation(new Animation(ani)); }
void SpriteExtend::addAnimation(Animation ani) { addAnimation(&ani); }
void SpriteExtend::addAnimation(Animation* ani) {
	animations.push_back(ani); addChild(ani);
}

void SpriteExtend::removeAnimation(Animation ani) { removeAnimation(&ani); }
void SpriteExtend::removeAnimation(Animation* ani) {
	vector<Animation*>::iterator pos;
	pos = find(animations.begin(), animations.end(), ani);
	if (pos != animations.end()) animations.erase(pos);
	removeChild(ani);
}
Animation* SpriteExtend::getAnimation(int id) { return animations[id]; }

void SpriteExtend::setMirror(bool mir) {

}
void SpriteExtend::updateOthers() {
	//Sprite::updateOthers();
	updateAnimations();
}
void SpriteExtend::updateAnimations() {
	vector<Animation*>::iterator pos;
	for (int i = animations.size() - 1; i >= 0; i--) {
		pos = animations.begin() + i;
		if ((*pos)->isEnded()) {
			delete* pos;
			removeAnimation(*pos);
			//animations.erase(pos);
		}
	}
}