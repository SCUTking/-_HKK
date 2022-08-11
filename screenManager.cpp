#include"stdafx.h"
#include <cstdlib>

#include"scene.h"
#include"screenManager.h"
using namespace std;
struct CONSOLE_FONT
{
	DWORD index;
	COORD dim;
};
//定义一些全局数据或变量
char** ScreenManager::data;// [GHeight][GWidth];
stack<Scene*> ScreenManager::scenes;//栈声明
DWORD ScreenManager::bytes = 0;
COORD ScreenManager::coord = { 0,0 };
bool ScreenManager::bufferSelector = false;
const double ScreenManager::FontSize = GFontSize;
const int ScreenManager::Width = GWidth;
const int ScreenManager::Height = GHeight;
int ScreenManager::goldtrue = 0;
int ScreenManager::dijibaScreen = 1;
int ScreenManager::idactor = 0;//diyige
//在类外声明两个缓冲区
HANDLE ScreenManager::hOutput, ScreenManager::hOutBuf;
void ScreenManager::setup() {
	createData();
	setupScreenSize();
	setupFontSize();
	setupScreenBuffers();
}

//未公布的API，下面进行动态载入
typedef BOOL(WINAPI* PROCSETCONSOLEFONT)(HANDLE, DWORD);
typedef BOOL(WINAPI* PROCGETCONSOLEFONTINFO)(HANDLE, BOOL, DWORD, CONSOLE_FONT*);
typedef COORD(WINAPI* PROCGETCONSOLEFONTSIZE)(HANDLE, DWORD);
typedef DWORD(WINAPI* PROCGETNUMBEROFCONSOLEFONTS)();
typedef BOOL(WINAPI* PROCGETCURRENTCONSOLEFONT)(HANDLE, BOOL, CONSOLE_FONT*);

PROCSETCONSOLEFONT SetConsoleFont;
PROCGETCONSOLEFONTINFO GetConsoleFontInfo;
PROCGETCONSOLEFONTSIZE GConsoleFontSize;
PROCGETNUMBEROFCONSOLEFONTS GetNumberOfConsoleFonts;
PROCGETCURRENTCONSOLEFONT GCurrentConsoleFont; 
void ScreenManager::setupFontSize() {
	int nNumFont;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HMODULE hKernel32 = GetModuleHandle(L"kernel32");

	SetConsoleFont = (PROCSETCONSOLEFONT)GetProcAddress(hKernel32, "SetConsoleFont");
	GetConsoleFontInfo = (PROCGETCONSOLEFONTINFO)GetProcAddress(hKernel32, "GetConsoleFontInfo");
	GConsoleFontSize = (PROCGETCONSOLEFONTSIZE)GetProcAddress(hKernel32, "GetConsoleFontSize");
	GetNumberOfConsoleFonts = (PROCGETNUMBEROFCONSOLEFONTS)GetProcAddress(hKernel32, "GetNumberOfConsoleFonts");
	GCurrentConsoleFont = (PROCGETCURRENTCONSOLEFONT)GetProcAddress(hKernel32, "GetCurrentConsoleFont");

	nNumFont = GetNumberOfConsoleFonts();
	CONSOLE_FONT* pFonts = new CONSOLE_FONT[nNumFont];
	GetConsoleFontInfo(hConsole, 0, nNumFont, pFonts);

	SetConsoleFont(hConsole, FontSize);
}

void ScreenManager::setupScreenBuffers() {

	//前者为默认版本，后者为双缓冲版本( hOutBuf)
	hOutput = CreateConsoleScreenBuffer(
		GENERIC_WRITE,//定义进程可以往缓冲区写数据
		FILE_SHARE_WRITE,//定义缓冲区可共享写权限
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	//获取默认标准显示缓冲区句柄
	//hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//创建新的缓冲区
	 hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	//设置新的缓冲区为活动显示缓冲，即控制台屏幕上出现
	//SetConsoleActiveScreenBuffer(hOutBuf);
	//隐藏两个缓冲区的光标-
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);
}
void ScreenManager::setupScreenSize() {//设置屏幕缓存区和控制台窗口大小
	char setting[30];
	sprintf_s(setting, "mode con:cols=%d lines=%d", Width, Height);//运用系统的system设置大小
	system(setting);
	
}
void ScreenManager::showScreen(HANDLE buf) {

	for (int y = 0; y < Height; y++) {
		coord.Y = y;
		WriteConsoleOutputCharacterA(buf, data[y], Width, coord, &bytes);
	}
	
	SetConsoleActiveScreenBuffer(buf);
}
void ScreenManager::createData() {//向缓冲区输出东西的data数组
	data = new char* [Height];
	for (int y = 0; y < Height; y++)
		data[y] = new char[Width];
	clearData();
}
void ScreenManager::clearData() {//清空数组
	for (int y = 0; y < Height; y++)
		for (int x = 0; x < Width; x++)
			data[y][x] = ' ';// 32 + (x + y) % 64;/////////////////////////////////////////////////////////
}
Scene* ScreenManager::currentScene() {
	return scenes.empty() ? NULL : scenes.top();
}
void ScreenManager::popScene() {
	if (scenes.empty()) return;
	if (currentScene() != NULL)
		delete currentScene();
	scenes.pop();
}
void ScreenManager::clearScene() {
	while (!scenes.empty()) popScene();
}
//自己搞的static void pushScene(Scene* scene,DisplayObject* b)
void ScreenManager::pushScene(Scene* scene, DisplayObject* b) {

	scene->addChild(b);
	scenes.push(scene);

}
void ScreenManager::pushScene(Scene* scene) {
	//scene->addChild(screenSprite);
	scenes.push(scene);
}

void ScreenManager::update() {
	//InputManager::update();
	Scene* scene = currentScene();
	//if (scene != NULL) scene->update();
}

void ScreenManager::render() {
	Scene* scene = currentScene();
	if (scene == NULL) clearData();
	else {
		clearData();
		scene->quickRender(data);
		ScreenManager::showScreen(bufferSelector ? hOutBuf : hOutput);
		bufferSelector = !bufferSelector;
	}
}
