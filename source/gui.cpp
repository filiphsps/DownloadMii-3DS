#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include <vector>
#include "utils.h"
#include "application.h"
#include "input.h"
#include "gui.h"
#include "main.h"
#include "download.h"
/* Images */
#include "offline_bin.h"

using namespace std;

navBar_s navbar;
u8* screenTopLeft = 0;
u8* screenTopRight = 0;
u8* screenBottom = 0;
extern char superStr[];
char buffer[256];
/* SCENE */
int scene = 0;
int maxScene = 3;
string sceneTitle;
vector<Application_s> tAppList;
int FPS;
u8* cimg;

/*
TopScreen: w400 h240
BottomScreen: w320 h240
*/

/* Used for the so called "scrolling" */
int VSPX = 0; 
int VSPY = 0;
int VSTX = 0; 
int VSTY = 0;

int butPos = 0;

void guiInit(){
	//ToDo
}

void setAppList(vector<Application_s> AppList){
	tAppList = AppList;
	//Reset the cords
	VSPY = 0;
	VSTY = 0;
}

void renderGUI(){
	for (int xzy = 0; xzy <= 1; xzy++){
		screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); 
		screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
		screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL); 
	
		/* Background */
		background();
	
		/* UI: TOP */
		drawTopBar();
		navbar.Title = sceneTitle;
	
		//TODO: Added a switch check for diffrent menus
		switch (currentMenu) {
		case 0: //Overview
			renderStoreFront();
			break;
		case 1: //Settings
			renderSettings();
			break;
		case 2: //App Page
			renderAppPage();
			break;
		case 3: //Downloads
			renderDownloads();
			break;
		case 4: //by dev
			break;
	}
}
	
	
	/* DEBUG */
	#ifdef DEBUG
	renderDebug();
	#endif
	
	/* Buffers */
	gfxFlushBuffers();
	gfxSwapBuffers();
	gspWaitForVBlank();
}


void renderStoreFront(){
	static int appn = 0;
	
	/* UI: TOP */
	if(cimg != NULL){
		gfxDrawSprite(GFX_TOP, GFX_LEFT, cimg, 192, 400, 0, 0);
		gfxDrawSprite(GFX_TOP, GFX_RIGHT, cimg, 192, 400, 0, 0);
	}
	/* UI: BOTTOM */
	
	/* Screen related UI(Changes based on scene) */
	switch(scene){
		case 0:
			for(auto app : tAppList){
				appn++;
				drawAppEntry(app, appn);
			}
			appn = 0;
			break;
		case 1:
			
			break;
		case 2:
			
			break;
		default:
			
			break;
	}
}

void renderSettings(){
	/* UI: TOP */
	if(cimg != NULL){ //ToDo: Render settings banner
		gfxDrawSprite(GFX_TOP, GFX_LEFT, cimg, 192, 400, 0, 0);
		gfxDrawSprite(GFX_TOP, GFX_RIGHT, cimg, 192, 400, 0, 0);
	}
	/* UI: BOTTOM */
	//ToDo
}

void renderAppPage(){
	/* UI: TOP */
	if(cimg != NULL){ //ToDo: Render app page banner
		gfxDrawSprite(GFX_TOP, GFX_LEFT, cimg, 192, 400, 0, 0);
		gfxDrawSprite(GFX_TOP, GFX_RIGHT, cimg, 192, 400, 0, 0);
	}
	/* UI: BOTTOM */
	
	//Text
	snprintf(buffer,256, "%s %s", (char*)currentApp.name.c_str(), (char*)currentApp.version.c_str());

	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackHeader,  buffer, 240 - fontBlackHeader.height,5);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, (char*)currentApp.publisher.c_str(), (240 - fontBlackHeader.height) - fontBlackSubHeader.height,5);
	
	//Download Button
	drawFillRect(0,190,320,240, 0,148,255, screenBottom); //Todo: use button as download status bar
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhiteHeader,  "Download", 15,113);
	
	//ToDo: We dont need to add & remove the button multiple times.
	clearVButtons();
	vButton_s but;
	but.ID = 0;
	but.x = 0;
	but.y = 190;
	but.x2 = 320;
	but.y2 = 240;
	but.menu = 0;
	addVButton(but);
	but.ID = 1;
	but.x = 5;
	but.y = fontBlackHeader.height;
	but.x2 = 315;
	but.y2 = (but.y + fontBlackHeader.height) + 10;
	addVButton(but);
}

void renderDownloads() {
	//ToDo
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, "This page will be implamented in version 1.1.0.0", 200, 5);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, "Or 1.2.0.0, press (B) to return to the main menu.", 180, 5);
}

void fadeOut(){
	for(int x = 255; x >= 0; x = x - 15){
		gfxFadeScreen(GFX_BOTTOM, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_RIGHT, x);
		gfxFlushBuffers(); 
		gfxSwapBuffers();
	}
}

void doKeyboard(char* inputText){
	//ToDo
}

/* Scenes */
int getOnScreenY(int vsy){
    return (vsy-VSPY);
}

/* UIs */
void drawAppEntry(Application_s app, int place){
	
    int y = 0;
	int butY = 0, butY2 = 0, butX2 = 302, butX = 200;
	if(place == 1){
		VSTY = APPLICATION_ENTRY_H;
		clearVButtons();
	}
	else{
		VSTY += APPLICATION_ENTRY_H;
	}
		
    y = (MARGIN * (place)) + (APPLICATION_ENTRY_H * (place - 1));
	
    if((getOnScreenY(y)>=240 || getOnScreenY(y)+APPLICATION_ENTRY_H <= 0) || VSPY >= VSTY){
		butPos = 0;
        return; //Outside screen dont draw
    }
    else if(getOnScreenY(y)+APPLICATION_ENTRY_H >= 240)/*The entry is partly offscreen*/
    {
        drawFillRect( 0,getOnScreenY(y), 320,239, 255,/*y/(float)VSTY**/255,255, screenBottom);
		
		//Button
		int x =  getOnScreenY(y)+(APPLICATION_ENTRY_H/4)*3 < 239 ? getOnScreenY(y)+(APPLICATION_ENTRY_H/4)*3 : 239;
		butX2 = x;
		int z = getOnScreenY(y) + APPLICATION_ENTRY_H/4 < 239 ? getOnScreenY(y) + APPLICATION_ENTRY_H/4 : 239;
		butX = z;
        drawFillRect( 200, z, 302,x, 0,148,255, screenBottom);
    }
    else if(getOnScreenY(y)<0)
    {
        drawLine(0,0,320,0,0,255,0,screenBottom);
        drawFillRect( 0,0, 320,getOnScreenY(y)+APPLICATION_ENTRY_H, 255,/*y/(float)VSTY**/255,255, screenBottom);
        drawLine( 0, getOnScreenY(y) + APPLICATION_ENTRY_H -1 , 320, getOnScreenY(y) + APPLICATION_ENTRY_H -1, 224,224,224, screenBottom);
		
		//Button
		butY = getOnScreenY(y) + APPLICATION_ENTRY_H/4 -1;
		butY2 = getOnScreenY(y)+(APPLICATION_ENTRY_H/4)*3 -1;
		drawFillRect( 200,butY, 302,butY2, 0,148,255, screenBottom);
    }
    else{
        drawFillRect( 0,getOnScreenY(y), 320,getOnScreenY(y)+APPLICATION_ENTRY_H, 255,/*y/(float)VSTY**/255,255, screenBottom);
        drawLine( 0, getOnScreenY(y) + APPLICATION_ENTRY_H -1 , 320, getOnScreenY(y) + APPLICATION_ENTRY_H -1, 224,224,224, screenBottom);
		
		//Button
		butY = getOnScreenY(y)+APPLICATION_ENTRY_H/4;
		butY2 = getOnScreenY(y)+(APPLICATION_ENTRY_H/4)*3;
		drawFillRect( 200,butY, 302,butY2, 0,148,255, screenBottom);
    }
	
    gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackHeader, (char*)app.name.c_str(),240-getOnScreenY( APPTITLE_MARGIN + y ), 5);
    gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, (char*)app.version.c_str(),240-getOnScreenY( APPVERSION_MARGIN + y ), 5);
	//Button
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhiteHeader, "Download",240-getOnScreenY( ((APPLICATION_ENTRY_H/4)*2 + fontWhiteHeader.height/2) + y ), 212);
	
	vButton_s but;
	but.ID = butPos;
	but.x = butX;
	but.y = butY;
	but.x2 = butX2;
	but.y2 = butY2;
	but.app = app;
	but.menu = 2;
	addVButton(but);
	butPos++;
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
void setStoreFrontImg(char* url){
	//w: 400
	//h: 192
	print("Downloading banner...\n");
	char* temp;
	u32 size;
	downloadFile(url, &temp, &size);
	cimg = (u8*)temp;
	print("Banner downloaded!\n");
	if(cimg[0] == 'e'){
		//Set banner to offline banner
		printf("Failed to dowload and set banner, defaulting to offline one\n");
		cimg = (u8*) offline_bin;
	}
}
void drawTopBar(){
	drawFillRect(0,0,400,NAVBAR_H, 0,126,216, screenTopLeft);
	drawFillRect(0,0,400,NAVBAR_H, 0,126,216, screenTopRight);
	drawFillRect(0,12,400,SECONDARY_NAVBAR_H + 12, 0,148,255, screenTopLeft);
	drawFillRect(0,12,400,SECONDARY_NAVBAR_H + 12, 0,148,255, screenTopRight);

	snprintf(buffer,256, (char*)navbar.Title.c_str());
	gfxDrawText(GFX_TOP, GFX_LEFT, &fontWhiteHeader, buffer, 240 - (((SECONDARY_NAVBAR_H / 2) + fontWhiteHeader.height)), 13);
	gfxDrawText(GFX_TOP, GFX_RIGHT, &fontWhiteHeader, buffer, 240 - (((SECONDARY_NAVBAR_H / 2) + fontWhiteHeader.height)), 13);
	
#ifdef DEBUG
	snprintf(buffer, 256, "%s, FPS: %d", APPLICATION_NAME, FPS);
#else
	snprintf(buffer, 256, "%s", APPLICATION_NAME);
#endif
	drawString(buffer, (400-strlen(APPLICATION_NAME)*8)/2,2, 255,255,255, screenTopLeft,GFX_TOP);
	drawString(buffer, (400-strlen(APPLICATION_NAME)*8)/2,2, 255,255,255, screenTopRight,GFX_TOP);
	
	u64 timeInSeconds = osGetTime() / 1000; 
	u64 dayTime = timeInSeconds % SECONDS_IN_DAY; 
	snprintf(buffer,256, "%llu:%llu:%llu",dayTime / SECONDS_IN_HOUR,(dayTime % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE,dayTime % SECONDS_IN_MINUTE);
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
