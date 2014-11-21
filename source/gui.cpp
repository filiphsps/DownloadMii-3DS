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
TopScreen: w400 h240
BottomScreen: w320 h240
*/

void initGUI(){
	
}

void renderGUI(){
	for(int x = 0; x <= 1; x++){ //Render twice
		/* Clear Screen */
		clearScreen(screenTopLeft, GFX_TOP); 
	 	clearScreen(screenTopRight, GFX_TOP); 

		/* UI */
		navBar();
		if(debug_l == true){
		
		}
		/* Buffers */
		gfxFlushBuffers(); 
	 	gfxSwapBuffers(); 
	 	//screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL); 
	 	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); 
	 	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL); 
	}
	
	gspWaitForEvent(GSPEVENT_VBlank0, false); //vSync
}
void debug(string text){
	debug_l = true;
	debugStr = text;
}
/* UIs */
void renderDebug(){
	char buffer[110];
	string debugStr = "";
	sprintf(buffer, const_cast<char*>(debugStr.c_str()));
	drawString(buffer, 5, 200, 178, 63, 255, screenTopLeft, GFX_TOP); 
 	drawString(buffer, 5, 200, 178, 63, 255,  screenTopRight, GFX_TOP);
}
void navBar(){ //ToDo: Change name to "topNavBar()"
	drawRect(0,0,400,60, 33,150,243, screenTopLeft);
	drawRect(0,0,400,60, 33,150,243, screenTopRight);
	
	char buffer[110];
	sprintf(buffer, APPLICATION_NAME);
	drawString(buffer, 5, 28, 255, 255, 255, screenTopLeft, GFX_TOP); 
 	drawString(buffer, 5, 28, 255, 255, 255, screenTopRight, GFX_TOP);
	
	sprintf(buffer, "            v1.0");
	drawString(buffer, 5, 28, 255, 255, 255, screenTopLeft, GFX_TOP); 
 	drawString(buffer, 5, 28, 255, 255, 255, screenTopRight, GFX_TOP);
}
