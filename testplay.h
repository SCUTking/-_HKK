#pragma once
#include"sprite.h"
class Sprite;
class CharDisplay : public Sprite {
public:
	static const int FontXCount;

	CharDisplay(int yCount);
	CharDisplay(string fileName, int yCount);
	CharDisplay(Bitmap* bitmap, int yCount);
	void setup(int index, int length);
	void setIndex(int index);
	void setLength(int length);

	int getFontWidth();
	int getFontHeight();

	void refresh();
private:

	int getFrameRectWidth();
	int getFrameRectHeight();
	int getFrameRectX();
	int getFrameRectY();

	void clearFrame();
	void refreshFrame();

	int index, length;
	int fontYCount;
};

class TextDisplay : public Sprite {
public:

	TextDisplay();
	TextDisplay(string fileName);
	TextDisplay(Bitmap* bitmap);
	~TextDisplay();
	void setLineHeightRate(double rate);
	virtual void setText(string text);
	virtual string getText();

	virtual int getWidth();
	virtual int getHeight();

	virtual void refresh();

protected:
	virtual void processText();
	virtual void processChar(int& lineHeight, char c);

	virtual int getCharIndex(char c);
	virtual int getCharLength(char c);

	virtual CharDisplay* addCharDisplay(char c);
	void clearCharDisplays();

	int textX, textY;
	int textWidth, textHeight;
	double lineHeightRate;

	Bitmap* fontFace;
	vector<CharDisplay*> charDisplays;
	string text;
};
class NumberDisplay : public TextDisplay {
public:

	NumberDisplay();
	NumberDisplay(string fileName);
	NumberDisplay(Bitmap* bitmap);

	virtual void setNum(int num);
	virtual int getNum();
protected:
	virtual void processText();
	virtual void processValue(int& lineHeight, int c);

	virtual int getValueIndex(int c);

	virtual CharDisplay* addCharDisplay(int c);

	int num;
};