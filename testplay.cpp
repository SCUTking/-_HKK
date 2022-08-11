#include "stdafx.h"

#include<stack>

#include "Database.h"
#include "testplay.h"
const int CharDisplay::FontXCount = 10;


CharDisplay::CharDisplay(int yCount = defaultFontYCount) {
	this->CharDisplay::CharDisplay(defaultFontFace, yCount);
}
CharDisplay::CharDisplay(string fileName, int yCount = defaultFontYCount) {
	this->CharDisplay::CharDisplay(Bitmap::getBitmap(fileName), yCount);
}
CharDisplay::CharDisplay(Bitmap* bitmap, int yCount = defaultFontYCount) : Sprite(bitmap) {
	fontYCount = yCount; setup(-1, 1);
}
int CharDisplay::getFontWidth() { return picturewidth; }
int CharDisplay::getFontHeight() { return getFrameRectHeight() / 2; }

int CharDisplay::getFrameRectX() {
	return (index % FontXCount) * getFrameRectWidth();
}
int CharDisplay::getFrameRectY() {
	return (index / FontXCount) * getFrameRectHeight();
}
int CharDisplay::getFrameRectWidth() {
	return picturewidth / FontXCount * length;
}
int CharDisplay::getFrameRectHeight() {
	return pictureheigth / fontYCount;
}
void CharDisplay::setup(int index, int length) {
	this->index = index;
	this->length = length;
	refresh();
}
void CharDisplay::setIndex(int index) {
	if (this->index != index) {
		this->index = index; refresh();
	}
}
void CharDisplay::setLength(int length) {
	if (this->length != length) {
		this->length = length; refresh();
	}
}
void CharDisplay::refresh() {
	if (index >= 0) refreshFrame();
	else clearFrame();
}
void CharDisplay::clearFrame() {
	setFrameRect(Rect(0, 0, 0, 0));
}
void CharDisplay::refreshFrame() {
	setFrameRect(Rect(getFrameRectX(), getFrameRectY(), getFrameRectWidth(), getFrameRectHeight()));
}



TextDisplay::TextDisplay() { this->TextDisplay::TextDisplay(defaultFontFace); }
TextDisplay::TextDisplay(string fileName) { this->TextDisplay::TextDisplay(Bitmap::getBitmap(fileName)); }
TextDisplay::TextDisplay(Bitmap* bitmap) { 
	this->resource = bitmap;
	this->pictureheigth = this->resource->height;
	this->picturewidth = this->resource->width;
	this->createdata();
	this->wholewritedata2();//更新data2
	fontFace = bitmap; setLineHeightRate(1.2); 
}
TextDisplay::~TextDisplay() { clearCharDisplays(); }

void TextDisplay::setLineHeightRate(double rate) {
	if (lineHeightRate != rate) {
		lineHeightRate = rate; refresh();
	}
}
void TextDisplay::setText(string text) {
	if (this->text != text) {
		this->text = text; refresh();
	}
}

string TextDisplay::getText() { return text; }

int TextDisplay::getWidth() { return textWidth; }
int TextDisplay::getHeight() { return textHeight; }

void TextDisplay::refresh() {

	clearCharDisplays();
	processText();
}
void TextDisplay::processText() {
	textWidth = textX = textY = 0; char c;
	int lineHeight = 0;
	for (int i = 0; i < text.size(); i++) {
		processChar(lineHeight, text[i]);
	}
	textWidth = max(textWidth, textX);
	textHeight = textY + lineHeight;
}
void TextDisplay::processChar(int& lineHeight, char c) {

	if (c == '\n') {
		textY += lineHeight; lineHeight = 0;
		textWidth = max(textWidth, textX);
		textX = 0;
	}
	else {
		CharDisplay* disp = addCharDisplay(c);
		disp->x = textX; disp->y = textY;
		lineHeight = max(lineHeight,
			int(disp->getFontHeight() * lineHeightRate));
		textX += disp->getFontWidth();
	}
}
int TextDisplay::getCharIndex(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'A' && c <= 'Z') return 10 + c - 'A';
	if (c >= 'a' && c <= 'z') return 40 + c - 'a';
	switch (c) {
	case ' ': return 36; break;
	case ',': return 37; break;
	case '.': return 38; break;
	case '-': return 39; break;
	case '!': return 66; break;
	case '?': return 67; break;
	case ':': return 68; break;
	case '*': return 69; break;
	case '/': return 70; break;
	case '(': return 71; break;
	case ')': return 72; break;
	case '[': return 73; break;
	case ']': return 74; break;
	case '+': return 75; break;
	case '=': return 76; break;
	case '_': return 77; break;
	case '%': return 78; break;
	case '&': return 79; break;
	default: return 36; break;
	}
}
int TextDisplay::getCharLength(char c) { return 1; }

CharDisplay* TextDisplay::addCharDisplay(char c) {
	CharDisplay* disp = new CharDisplay(fontFace);
	disp->setup(getCharIndex(c), getCharLength(c));
	charDisplays.push_back(disp);

	disp->visible = 1;//让其能渲染出来
	addChild(disp);
	return disp;
}
void TextDisplay::clearCharDisplays() {

	for (int i = 0; i < charDisplays.size(); i++) {
		removeChild(charDisplays[i]);
		delete charDisplays[i];
	}
	charDisplays.clear();
}

NumberDisplay::NumberDisplay() { this->NumberDisplay::NumberDisplay(defaultFontFace); }
NumberDisplay::NumberDisplay(string fileName) { this->NumberDisplay::NumberDisplay(Bitmap::getBitmap(fileName)); }
NumberDisplay::NumberDisplay(Bitmap* bitmap) { fontFace = bitmap; setLineHeightRate(1.2); }

void NumberDisplay::setNum(int num) {
	if (this->num != num) {
		this->num = num; this->clearCharDisplays(); processText();
	}
}
int NumberDisplay::getNum() { return num; }

void NumberDisplay::processText() {
	textWidth = textX = textY = 0; char c;
	int lineHeight = 0;
	processValue(lineHeight, num);
	textWidth = max(textWidth, textX);
	textHeight = textY + lineHeight;
}
void NumberDisplay::processValue(int& lineHeight, int c) {
	stack<int> numBit;
	do {
		numBit.push(c % 10); c /= 10;
	} while (c > 0);
	while (!numBit.empty()) {
		int num = numBit.top(); numBit.pop();
		CharDisplay* disp = addCharDisplay(num);
		disp->x = textX; disp->y = textY;
		lineHeight = max(lineHeight,
			int(disp->getFontHeight() * lineHeightRate));
		textX += disp->getFontWidth();
	}
}
CharDisplay* NumberDisplay::addCharDisplay(int c) {
	CharDisplay* disp = new CharDisplay(fontFace);
	disp->setup(getValueIndex(c), getCharLength(c));
	charDisplays.push_back(disp);
	addChild(disp);
	return disp;
}
int NumberDisplay::getValueIndex(int c) { return c; }
