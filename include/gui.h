#pragma once

#include <iostream>
#include <string.h>
#include "input.h"
#include "draw.h"
#include "ascii64.h"

#define print(...) sprintf(&superStr[strlen(superStr)], __VA_ARGS__);
/* FLAT DESIGN UI */
#define TOPSCREEN_W 400
#define TOPSCREEN_H 240
#define BOTTOMSCREEN_W 320
#define BOTTOMSCREEN_H 240
#define APPLICATION_ENTRY_W 295
#define APPLICATION_ENTRY_H 50
#define NAVBAR_H 12
#define SECONDARY_NAVBAR_H 36
#define SHADOW_ANGLE 135

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

/* TEXT */
void cutLine(char* str);
int countLines(char* str);