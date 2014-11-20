#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include "utils.h"
#include "application.h"
#include "input.h"
#include "gui.h"

using namespace std;

/*
I think thats right ;)
TopScreen: w400 h240
BottomScreen: w320 h240
*/

void initGUI(){
	
}

void renderGUI(){
	navBar(); //Draw navBar
	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
	//screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL);
	gfxSwapBuffersGpu(); 
	gspWaitForEvent(GSPEVENT_VBlank0, false); 
}

/* UIs */
void navBar(){
	drawRect(0,0,400,20, 0xFF,0xFF,0xFF, screenTopLeft);
	drawRect(0,0,400,20, 0xFF,0xFF,0xFF, screenTopRight);
}