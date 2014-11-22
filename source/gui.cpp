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
	//ToDo
}

void renderGUI(){
	for(int x = 0; x <= 1; x++){
		screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL); 
		screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); 
		screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
		/* Clear Screen */
		clearScreen(screenBottom, GFX_TOP);
		clearScreen(screenTopLeft, GFX_TOP); 
		clearScreen(screenTopRight, GFX_TOP);

		/* Background */
		background();

		/* UI: TOP */
		
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
 	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, superStr, 240-fontDefault.height*4, 20); 
}
void background(){
	drawFillRect( 0, 0, 400, 240, 0,148,255, screenTopLeft);
	drawFillRect( 0, 0, 400, 240, 0,148,255, screenTopRight);
	drawFillRect( 0, 0, 320, 240, 0,148,255, screenBottom);
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
