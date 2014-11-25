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
#define APPLICATION_ENTRY_W 290
#define APPLICATION_ENTRY_H 50
#define NAVBAR_H 12
#define SECONDARY_NAVBAR_H 36
#define SHADOW_ANGLE 135
#define MARGIN 12

using namespace std;

struct navBar_s{
	string Title;
	
};

static u8* screenTopLeft = 0;
static u8* screenTopRight = 0;
static u8* screenBottom = 0;
extern char superStr[];

void initGUI(); 
void renderGUI();
void renderDebug();

/* UIs */
void drawTopBar(char* Title);
void background();
void renderOverview();
void drawAppEntry(Application_s app, int place);

/* TEXT */
void cutLine(char* str);
int countLines(char* str);

/* SCENE */
static unsigned int scene = 0;
static unsigned int maxScene = 2;
static char* sceneTitle = "";