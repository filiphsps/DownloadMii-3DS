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

int VirtualScreenW = 400; //Used for scrolling
int VirtualScreenH = 240;

void initGUI(){
	//ToDo
}

//Todo: add scrolling to the whole app!!!

void renderGUI(){
	Application_s app2 = defineApplication_s(1, "name", "owner");
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
	navbar.Title = "Applications"; //ToDo
	drawTopBar();
	
	/* UI: BOTTOM */
	
	/* DEBUG */
	renderDebug();
	
	/* Screen related UI(Changes based on scene) */
	switch(scene){
		case 0:
			renderOverview();
			drawAppEntry(app2, 1);
			drawAppEntry(app2, 2);
			drawAppEntry(app2, 3);
			drawAppEntry(app2, 4);
			drawAppEntry(app2, 5);
			break;
		case 1:
			
			break;
		case 2:
			
			break;
		default:
			
			break;
	}
	
	/* Buffers */
	gfxFlushBuffers(); 
	gfxSwapBuffers();
}




/* Scenes */

void renderOverview(){ //Renders a nice overview of the top apps for the user

}


/* UIs */
void drawAppEntry(Application_s app, int place){
	//Very hacky way to display an app list
	int y = 0;
	y = (MARGIN * (place)) + (APPLICATION_ENTRY_H * (place - 1));
	
	if(y >= 240){
		return; //Outside screen dont draw
	}
	if(y  + APPLICATION_ENTRY_H >= 240)
	{
		drawFillRect( 15, y, 305, 240, 255,255,255, screenBottom);
		drawRect( 15, y, 305, 241, 224,224,224, screenBottom); //ToDo: change to a light gray
		drawLine( 0, 241, 320, 241,  240, 242, 253, screenBottom); //Removes the black ugly row at the top 
	}
	else{
		drawFillRect( 15, y, 305, y + APPLICATION_ENTRY_H, 255,255,255, screenBottom);
		drawRect( 15, y, 305, y + APPLICATION_ENTRY_H, 224,224,224, screenBottom); //ToDo: change to a light gray
	}
	stringstream s;
    s << app.Name << " (" << y << ")";
	app.Name = s.str();
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlack, (char*)app.Name.c_str(), (VirtualScreenH - y) + APPTITLE_MARGIN, 20); 
}
void renderDebug(){
	int i = countLines(superStr); 
 	while(i>200/fontDefault.height-3){cutLine(superStr);i--;} 
	gfxDrawText(GFX_TOP, GFX_LEFT, &fontBlack, superStr, (240-fontDefault.height*5)+6, 6); 
	gfxDrawText(GFX_TOP, GFX_RIGHT, &fontBlack, superStr, (240-fontDefault.height*5)+6, 6); 
}
void background(){
	drawFillRect( 0, 0, 320, 240, 227,242,253, screenBottom);
	drawFillRect( 0, 0, 400, 240, 227,242,253, screenTopLeft);
	drawFillRect( 0, 0, 400, 240, 227,242,253, screenTopRight);
}
void drawTopBar(){
	char buffer[100];
	sprintf(buffer, navbar.Title.c_str());
	drawFillRect(0,0,400,NAVBAR_H, 0,126,216, screenTopLeft);
	drawFillRect(0,0,400,NAVBAR_H, 0,126,216, screenTopRight);
	drawFillRect(0,12,400,SECONDARY_NAVBAR_H + 12, 0,148,255, screenTopRight);
	drawFillRect(0,12,400,SECONDARY_NAVBAR_H + 12, 0,148,255, screenTopRight);
	
	drawString(APPLICATION_NAME, (400-strlen(APPLICATION_NAME)*8)/2,2, 255,255,255, screenTopLeft,GFX_TOP);
	drawString(APPLICATION_NAME, (400-strlen(APPLICATION_NAME)*8)/2,2, 255,255,255, screenTopRight,GFX_TOP);
	
	gfxDrawText(GFX_TOP, GFX_LEFT, &fontWhiteHeader, buffer, 237 - (((SECONDARY_NAVBAR_H/2) + fontWhiteHeader.height)), 13); 
	gfxDrawText(GFX_TOP, GFX_RIGHT, &fontWhiteHeader, buffer, 237 - (((SECONDARY_NAVBAR_H/2) + fontWhiteHeader.height)), 13); 
	
	u64 timeInSeconds = osGetTime() / 1000; 
	u64 dayTime = timeInSeconds % SECONDS_IN_DAY; 
	sprintf(buffer, "%llu:%llu:%llu",dayTime / SECONDS_IN_HOUR,(dayTime % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE,dayTime % SECONDS_IN_MINUTE);
	drawString(buffer, 2,2, 255,255,255, screenTopLeft,GFX_TOP);
	drawString(buffer, 2,2, 255,255,255, screenTopRight,GFX_TOP);
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
