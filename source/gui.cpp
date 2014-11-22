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
#include "main.h"

using namespace std;

/*
(They should be inverted for some reason)
TopScreen: w400 h240
BottomScreen: w320 h240
*/

void initGUI(){
	screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL); 
 	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); 
 	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL); 	
}

void renderGUI(){
	/* Clear Screen */
	clearScreen(screenTopLeft, GFX_TOP); 
 	clearScreen(screenTopRight, GFX_TOP);

	/* White BG */
	whiteBG();

	/* UI */
	//navBar(); //Might be the problem we are facing.
	if(DEBUG == true){
		//renderDebug();
	}
	/* Buffers */
	screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL); 
 	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); 
 	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL); 
	gfxFlushBuffers(); 
 	gfxSwapBuffers(); 
}
void debug(char* text){
	debugStr = text;
}
/* UIs */
void renderDebug(){
	char buffer[110];
	sprintf(buffer, debugStr);
	drawString(buffer, 28, 200, 178, 63, 255, screenTopLeft, GFX_TOP); 
 	drawString(buffer, 28, 200, 178, 63, 255,  screenTopRight, GFX_TOP);
}
void navBar(){ //ToDo: Change name to "topNavBar()"
	drawRect(0,0,60,400, 33,150,243, screenTopLeft);
	drawRect(0,0,60,400, 33,150,243, screenTopRight);
	
	char buffer[110];
	sprintf(buffer, APPLICATION_NAME);
	drawString(buffer, 28, 5, 255, 255, 255, screenTopLeft, GFX_TOP); 
 	drawString(buffer, 28, 5, 255, 255, 255, screenTopRight, GFX_TOP);
	
	sprintf(buffer, "            v1.0");
	drawString(buffer, 28, 5, 255, 255, 255, screenTopLeft, GFX_TOP); 
 	drawString(buffer, 28, 5, 255, 255, 255, screenTopRight, GFX_TOP);
}
void whiteBG(){
	drawFillRect( 0, 0, 240, 400, 255, 255, 255, screenTopLeft);
	drawFillRect( 0, 0, 240, 400, 255, 255, 255, screenTopRight);
	drawFillRect( 0, 0, 240, 400, 255, 255, 255, screenBottom);
}
