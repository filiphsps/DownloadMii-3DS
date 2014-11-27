#pragma once

#include <iostream>
#include <string.h>
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
#define APPTITLE_MARGIN (APPLICATION_ENTRY_H/2) - (fontBlack.height)

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

void initGUI(); 
void renderGUI();
void renderDebug();

/* UIs */
void drawTopBar();
void background();
void renderOverview();
void drawAppEntry(Application_s app, int place);

/* TEXT */
void cutLine(char* str);
int countLines(char* str);

/* SCENE */
extern unsigned int scene;
extern unsigned int maxScene;
extern char* sceneTitle;