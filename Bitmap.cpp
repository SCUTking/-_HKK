#include"stdafx.h"
#include"Bitmap.h"

#include"Database.h"



using namespace std;

map<string, Bitmap> Bitmap::bitmapCache;
map<int, Bitmap> Bitmap::iconCache;
vector<Bitmap> Bitmap::otherBitmaps;
Bitmap* Bitmap::getBitmap(string str) {
	//return new Bitmap(str);
	if (bitmapCache.count(str) <= 0) bitmapCache[str] = Bitmap(str);
	return &bitmapCache[str];
}
Bitmap::Bitmap(string fileName) {//构造函数
	url = fileName;
	readFromFile(url);
}
Bitmap::Bitmap() {

	width = height = 0;
}
Bitmap::Bitmap(int width, int height) {
	url = "custom";
	createEmpty(width, height);
}
void Bitmap::readFromFile(string fileName) {//将每个文件变成一个bitmap，bitmap中data就是文件的内容
	string fileData = "";
	height = 0; width = 0;
	ifstream file;
	file.open(fileName, ios::in); // ļ ֶȡ
	char c;
	file >> noskipws;//no skip whilesapce不忽视空格
	while (!file.eof()) {
		file >> c;
		if (c == '\n') height++;
		else { if (height == 0) width++; fileData += c; }
	}
	data1 = new char* [++height];
	for (int i = 0, y = 0; y < height; y++) {
		data1[y] = new char[width];
		for (int x = 0; x < width; x++) data1[y][x] = fileData[i++];
	}
	file.clear();
}
int Bitmap::getWidth() {
	return width;
}
int Bitmap::getHeight() {
	return height;
}
void Bitmap::createEmpty(int width, int height) {
	this->width = width;
	this->height = height;

	data1 = new char* [height];
	for (int y = 0; y < height; y++) {
		data1[y] = new char[width];
		for (int x = 0; x < width; x++) data1[y][x] = 'T';
	}
}


