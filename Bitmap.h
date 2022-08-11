#pragma once

#include<vector>
#include<fstream>
#include<map>

//#include "Rect.h"
using namespace std;

class Bitmap {
public:
	static Bitmap* getBitmap(string str);
	
	Bitmap();//δ�Ѷ�̬��Ա���ڹ��캯������ע��
	Bitmap(string fileName);
	Bitmap(int width, int height);

	int getWidth();
	int getHeight();


	void createEmpty(int width, int height);
	int width, height;
	char** data1;//�ֲ�
	void readFromFile(string fileName);
	string url;

	static map<string, Bitmap> bitmapCache;
	static map<int, Bitmap> iconCache;
	static vector<Bitmap> otherBitmaps;
};