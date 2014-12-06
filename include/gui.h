#pragma once

#include <iostream>
#include <string.h>
#include <vector>
#include <3ds.h>
#include "input.h"
#include "draw.h"
#include "ascii64.h"
#include "application.h"

#define print(...) sprintf(&superStr[strlen(superStr)], __VA_ARGS__);
/* FLAT DESIGN UI */
#define TOPSCREEN_W 400
#define TOPSCREEN_H 240
#define BOTTOMSCREEN_W 320
#define BOTTOMSCREEN_H 240
#define APPLICATION_ENTRY_W 320
#define APPLICATION_ENTRY_H 75
#define NAVBAR_H 12
#define SECONDARY_NAVBAR_H 36
#define SHADOW_ANGLE 135
#define MARGIN 0 //No margin
#define APPTITLE_MARGIN ((APPLICATION_ENTRY_H/2) - fontBlackHeader.height) + 12
#define APPVERSION_MARGIN ((APPLICATION_ENTRY_H/2) - fontBlackSubHeader.height) + 24

using namespace std;

struct navBar_s{
	string Title;
	int ID;
	//ToDo
};
extern navBar_s navbar;
extern u8* screenTopLeft;
extern u8* screenTopRight;
extern u8* screenBottom;
extern char superStr[];

extern int currentMenu; //0 = overview, 1 = settings, 2 = app page, 3 = downloads(When i fugure out multicore), 4 = by dev.
extern Application_s currentApp;

extern int VSPY;
extern int VSPX;
extern int VSTY;
extern int VSTX;

void guiInit(); 
void renderGUI();
void renderStoreFront();
void renderSettings();
void renderAppPage();
void renderDebug();
void setAppList(vector<Application_s>* AppList);

/* UIs */
void drawTopBar();
void setStoreFrontImg(char* url); //Needs to be: 400x192
void background();
void drawAppEntry(Application_s app, int place);

/* TEXT */
void cutLine(char* str);
int countLines(char* str);

/* SCENE */
extern unsigned int scene;
extern unsigned int maxScene;
extern char* sceneTitle;