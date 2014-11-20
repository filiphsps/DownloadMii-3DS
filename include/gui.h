#ifndef __GUI_H__
#define __GUI_H__

#include <iostream>
#include <string.h>
#include "input.h"
#include "draw.h"
#include "ascii64.h"

using namespace std;

struct navBar_s{
	string Title;
	
};

static u8* screenTopLeft = 0;
static u8* screenTopRight = 0;
static u8* screenBottom = 0;

void initGUI();
void renderGUI();

/* UIs */
void navBar();
#endif