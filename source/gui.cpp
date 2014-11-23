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
#include "background_bin.h"

using namespace std;

/*
TopScreen: w400 h240
BottomScreen: w320 h240
*/

void initGUI(){
	//ToDo
}

void renderGUI(){
	for(int x = 0; x <= 1; x++){
		screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); 
		screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
		screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL); 
		/* Clear Screen */
		clearScreen(screenBottom, GFX_BOTTOM);
		clearScreen(screenTopLeft, GFX_TOP); 
		clearScreen(screenTopRight, GFX_TOP);

		/* Background */
		background();
		
		/* UI: TOP */
		drawTopBar();
		
		/* UI: BOTTOM */
		
		/* DEBUG */
		renderDebug();
		
		/* Buffers */
		gfxFlushBuffers(); 
		gfxSwapBuffers();
	}
}
/* UIs */
void renderDebug(){
	int i = countLines(superStr); 
 	while(i>240/fontDefault.height-3){cutLine(superStr);i--;} 
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, superStr, 240-fontDefault.height*2, 2); 
	gfxDrawText(GFX_TOP, GFX_RIGHT, NULL, superStr, 240-fontDefault.height*2, 2); 
}
void background(){
	drawFillRect( 0, 0, 320, 240, 0,148,255, screenBottom);
	drawFillRect( 0, 0, 400, 240, 0,148,255, screenTopLeft);
	drawFillRect( 0, 0, 400, 240, 0,148,255, screenTopRight);
	
	//Background
	gfxDrawDualSprite((u8*)background_bin, 240, 400, 240, 0);
	
	//L
	/*drawFillRect( 0, 200, 60, 240, 0,126,216, screenTopLeft);
	drawFillRect( 0, 200, 60, 240, 0,126,216, screenTopRight);
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, "L", 12, 27); 
	gfxDrawText(GFX_TOP, GFX_RIGHT, NULL, "L", 12, 27); 
	//R
	drawFillRect( 340, 200, 400, 240, 0,126,216, screenTopLeft);
	drawFillRect( 340, 200, 400, 240, 0,126,216, screenTopRight);
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, "R", 12, 367); 
	gfxDrawText(GFX_TOP, GFX_RIGHT, NULL, "R", 12, 367); */
}
void drawTopBar(){
	drawFillRect(0,0,400,12, 0,126,216, screenTopLeft);
	drawFillRect(0,0,400,12, 0,126,216, screenTopRight);
	drawString(APPLICATION_NAME, (400-strlen(APPLICATION_NAME)*8)/2,2, 255,255,255, screenTopLeft,GFX_TOP);
	drawString(APPLICATION_NAME, (400-strlen(APPLICATION_NAME)*8)/2,2, 255,255,255, screenTopRight,GFX_TOP);
	char buffer[100];
	u64 timeInSeconds = osGetTime() / 1000; 
	u64 dayTime = timeInSeconds % SECONDS_IN_DAY; 
	sprintf(buffer, "%llu:%llu:%llu",dayTime / SECONDS_IN_HOUR,(dayTime % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE,dayTime % SECONDS_IN_MINUTE);
	drawString(buffer, 2,2, 255,255,255, screenTopLeft,GFX_TOP);
	drawString(buffer, 2,2, 255,255,255, screenTopRight,GFX_TOP);
}
void renderTopNavBar(){
	drawFillRect( 0, 0, 400, 40, 255,255,255, screenTopLeft);
	drawFillRect( 0, 0, 400, 40, 255,255,255, screenTopRight);
}
int countLines(char* str)
{
	if(!str)return 0;
	int cnt; for(cnt=1;*str=='\n'?++cnt:*str;str++);
	return cnt;
}
void cutLine(char* str)
{
	if(!str || !*str)return;
	char* str2=str;	for(;*str2&&*(str2+1)&&*str2!='\n';str2++);	str2++;
	memmove(str,str2,strlen(str2)+1);
}
