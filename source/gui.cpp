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
	for(int x = 0; x <= 1; x++){ //Render twice
		/* Clear Screen */
		clearScreen(screenTopLeft, GFX_LEFT); 
	 	clearScreen(screenTopRight, GFX_LEFT); 

		/* UI */
		navBar();
		
		/* Buffers */
		gfxFlushBuffers(); 
	 	gfxSwapBuffers(); 
	 	//screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL); 
	 	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); 
	 	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL); 
	}
	
	gspWaitForEvent(GSPEVENT_VBlank0, false); //vSync
}

/* UIs */
void navBar(){ //ToDo: Change name to "topNavBar()"
	drawRect(0,0,400,60, 255,255,255, screenTopLeft);
	drawRect(0,0,400,60, 255,255,255, screenTopRight);
	
	char buffer[110];
	sprintf(buffer, "DownloadMii" + " " + " v1.0"); //ToDo: create a "main.h" file that defines the app name
	drawString(buffer, 5, 28, 255, 255, 255, screenTopLeft, GFX_LEFT); 
 	drawString(buffer, 5, 28, 255, 255, 255, screenTopRight, GFX_LEFT); 
}
