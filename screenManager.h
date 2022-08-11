#pragma once
#include"scene.h"
#include<stack>
#include"scene.h"
#include"DisplayObject.h"
#include<Windows.h>//sleep等函数的头文件
using namespace std;
//#include"sprite.h"
//定义一些系统的变量 比如窗口大小，字体
#define GFontSize 0
#define GHeight 500
#define GWidth 800
#define SHeight  170
#define SWidth  640
class DisplayObject;
class Scene;
static class ScreenManager {
public:
	static void pushScene(Scene* scene,DisplayObject* b);
	static void show();


	static void setup();
	static void clearData();
	static void createData();

	static void showScreen(HANDLE buf);

	static void render();
	static void update();

	static void popScene();
	static void clearScene();
	static void pushScene(Scene* scene);
	//static void gotoScene(Scene* scene);
	//static void resetToScene(Scene* scene);
	static Scene* currentScene();

	//static void setScreenCursorPosition(int x, int y);

	static HANDLE hOutput, hOutBuf;//̨Ļ
	static DWORD bytes;//

	static const int Height ;
	static const int Width;

	static char** data;// [GHeight][GWidth];



	//static Sprite* screenSprite;
    

	static int goldtrue;
	static int dijibaScreen;
	static int idactor;

private:
	static bool bufferSelector;
	static void setupScreenSize();
	static void setupFontSize();
	static void setupScreenBuffers();
	static void setupScreenSprite();

	static COORD coord;//缓冲区输出的起始指针

	
	static const double FontSize;

	static stack<Scene*> scenes;
};


