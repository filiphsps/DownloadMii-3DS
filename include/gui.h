#pragma once

#include <iostream>
#include <string.h>
#include "input.h"
#include "draw.h"
#include "ascii64.h"

#define print(...) sprintf(&superStr[strlen(superStr)], __VA_ARGS__); renderGUI()

using namespace std;

struct navBar_s{
	string Title;
	
};

static u8* screenTopLeft = 0;
static u8* screenTopRight = 0;
static u8* screenBottom = 0;
static char superStr[8192] = "";

void initGUI(); 
void renderGUI();

/* UIs */
void renderDebug();
void background();

/* TEXT */
void cutLine(char* str);
int countLines(char* str);