#pragma once
#include<conio.h>
#include<Windows.h>
#include"DisplayObject.h"
#include"Spritecmd.h"
#include"scene.h"
char keyboard_actor(DisplayObject* obj);
int keyboard_select_Scenestart(DisplayObject* a);
int keyboard_select_SceneMenu(DisplayObject* a);
int keyboard_select_SceneMenu_mapwindow(DisplayObject* a);
int keyboard_select_SceneMenu_maplevelwindow(DisplayObject* a);
int keyboard_select_SceneMenu_shopwindow(DisplayObject* a, int& goldtrue);