

#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdio.h>//STD_OUTPUT_HANDLE��Ӧͷ�ļ�
#include<stdlib.h>
#include<conio.h>

#include<Windows.h>//sleep�Ⱥ�����ͷ�ļ�

#include"screenManager.h"
#include"Database.h"
#include"scene.h"
#include"Spritecmd.h"
using namespace std;




int main() {
	ScreenManager::setup();
	initDatabase();
	Scenestart* ab = new Scenestart();
	ScreenManager::pushScene(ab);
	while (1) {
		ScreenManager::render();
	}
}