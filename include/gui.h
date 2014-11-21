#pragma once


#include <iostream>
#include <string.h>
#include "input.h"
#include "draw.h"
#include "ascii64.h"

using namespace std;

struct navBar_s{
	string Title;
	
};

static char* debugStr;
static u8* screenTopLeft = 0;
static u8* screenTopRight = 0;
static u8* screenBottom = 0;

void initGUI(); 
void renderGUI();
void debug(char* text);

/* UIs */
void navBar();
void renderDebug();
void whiteBG();