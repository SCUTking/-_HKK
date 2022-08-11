#pragma once

#include<vector>
#include<fstream>
#include<map>

//#include "Rect.h"
using namespace std;

class Bitmap {
public:
	static Bitmap* getBitmap(string str);
	
	Bitmap();//未把动态成员放在构造函数中请注意
	Bitmap(string fileName);
	Bitmap(int width, int height);

	int getWidth();
	int getHeight();


	void createEmpty(int width, int height);
	int width, height;
	char** data1;//局部
	void readFromFile(string fileName);
	string url;

	static map<string, Bitmap> bitmapCache;
	static map<int, Bitmap> iconCache;
	static vector<Bitmap> otherBitmaps;
};