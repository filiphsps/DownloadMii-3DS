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
#include "settings.h"
/* Images */
#include "offline_bin.h"
#include "Installed_bin.h"
#include "Update_bin.h"
#include "Error_bin.h"
#include "ButtonL_bin.h"
#include "ButtonR_bin.h"

using namespace std;

/* UI */
Screen_s screen;
navBar_s navbar;
progressBar_s progressbar;

extern char superStr[];
font_s debugfnt = fontWhite;
char buffer[256];
/* SCENE */
int scene = 0;
int maxScene = 3;
string sceneTitle;
vector<Application_s> tAppList;
vector<Category_s> tCatList;
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

void draw() {
	/* DEBUG */
#ifdef DEBUG
	renderDebug();
#endif

	/* Buffers */
	gfxFlushBuffers();
	gfxSwapBuffers();
}

void renderGUI(){
	for (int xzy = 0; xzy <= 1; xzy++){
		screen.screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
		screen.screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
		screen.screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
	
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
			renderByDev();
			break;
		}
	}
}

void renderByDev() {
	int appn = 0;
	for (auto app : tAppList) {
		appn++;
		drawAppEntry(app, appn);
	}
	appn = 0;
}
inline void drawAppEntries() {
	int appn = 0;
	for (auto app : tAppList) {
		appn++;
		drawAppEntry(app, appn);
	}
	appn = 0;
}
inline void drawCatEntries() {
	int cn = 0;
	for (auto cat : tCatList) {
		cn++;
		drawCategory(cat, cn, false);
	}
	cn = 0;
}
void renderStoreFront(){
	
	int temp; //ToDo: migrate to gui.h #define

	/* UI: TOP */
	if(cimg != NULL){
		gfxDrawSprite(GFX_TOP, GFX_LEFT, cimg, 192, 400, 0, 0);
		gfxDrawSprite(GFX_TOP, GFX_RIGHT, cimg, 192, 400, 0, 0);
	}
	/* UI: BOTTOM */
	
	/* Screen related UI(Changes based on scene) */
	switch(scene){
		case -1:
			//ToDo: searchbox
			//ToDo: allow the user to select category from a list of categories
			//temp = (250 - fontBlackHeader.height) - fontBlackSubHeader.height;
			//gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, "This will be implemented in a future update!", (temp - fontBlackHeader.height) + 4, 5);
			drawCatEntries();
			break;
		case 0:
			drawAppEntries();
			break;
		case 1:
			drawAppEntries();
			break;
		case 2:
			drawAppEntries();
			break;
		case 3:
			drawAppEntries();
			break;
		default:
			
			break;
	}
	if (settings.internetConnection) {
		gfxDrawSprite(GFX_TOP, GFX_LEFT, (u8*)ButtonL_bin, 40, 40, 10, 10);
		gfxDrawSprite(GFX_TOP, GFX_RIGHT, (u8*)ButtonL_bin, 40, 40, 10, 10);

		gfxDrawSprite(GFX_TOP, GFX_LEFT, (u8*)ButtonR_bin, 40, 40, 10, 350);
		gfxDrawSprite(GFX_TOP, GFX_RIGHT, (u8*)ButtonR_bin, 40, 40, 10, 350);
	}
	else {
		sceneTitle = "Installed Applications";
	}

	if (tAppList.empty()) {
		temp = (250 - fontBlackHeader.height) - fontBlackSubHeader.height;
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, "This category looks empty...\nplease come back at a later date.", (temp - fontBlackHeader.height) + 4, 5);
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

void renderUpdate(char* cv, char* rv) {
	/* Background */
	background();

	/* UI: TOP */
	drawTopBar();
	navbar.Title = sceneTitle;
	if (cimg != NULL) { //ToDo: Render app page banner
		gfxDrawSprite(GFX_TOP, GFX_LEFT, cimg, 192, 400, 0, 0);
		gfxDrawSprite(GFX_TOP, GFX_RIGHT, cimg, 192, 400, 0, 0);
	}
	/* UI: BOTTOM */
	//Text
	snprintf(buffer, 256, "%s->%s!", cv, rv);

	int temp = (240 - fontBlackHeader.height) - fontBlackSubHeader.height;
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackHeader, buffer, 240 - fontBlackHeader.height, 5);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, (char*)currentApp.publisher.c_str(), temp, 5);

	//About text
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, "There is an update available, download?\nPress (B) to skip the update.\n(The application will close when the \ninstallation is done)", (temp - fontBlackHeader.height) + 4, 5); //Should be a new line every ~35 chars

																																		   //Download Button
	drawFillRect(0, 190, 320, 240, 0, 148, 255, screen.screenBottom);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhiteHeader, "Update", 15, 116);

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

	int temp = (240 - fontBlackHeader.height) - fontBlackSubHeader.height;
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackHeader,  buffer, 240 - fontBlackHeader.height,5);
	snprintf(buffer, 256, "%s; %d Downloads", (char*)currentApp.publisher.c_str(), currentApp.downloads);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, buffer, temp,5);
	
	//About text
	string description = insert_newlines(currentApp.description, 50);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader,  (char*)description.c_str(), (temp - fontBlackHeader.height) + 4,5);

	//Download Button
	if (settings.internetConnection) {
		drawFillRect(1, 190, 320, 240, 0, 148, 255, screen.screenBottom);
		if (progressbar.used) {
			int width = (progressbar.progress * 320) / progressbar.maxProgress;
			drawFillRect(1, 190, width, 240, 42, 149, 10, screen.screenBottom);
		}
	}
	else {
		drawFillRect(1, 190, 320, 240, 200, 200, 200, screen.screenBottom);
	}

	if(!currentApp.installed && !currentApp.updateAvalible && !currentApp.error)
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhiteHeader,  "Download", 15,113);
	else if(currentApp.installed && !currentApp.updateAvalible && !currentApp.error)
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhiteHeader, "Re-Download", 15, 113);
	else if(currentApp.installed && currentApp.updateAvalible && !currentApp.error)
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhiteHeader, "Update", 15, 118);
	else if (currentApp.error)
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhiteHeader, "Fix Application", 15, 113);
	
	//ToDo: We dont need to add & remove the button multiple times.
	if (settings.internetConnection) {
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
		//addVButton(but);
	}
}

void renderDownloads() {
	//ToDo
	if (progressbar.progress > 0) {
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, "Downloading...", 230, 5);
	}
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, "This page will be implemented in version 1.1/1.2", 200, 5);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, "press (B) to return to the main menu.", 180, 5);
}

void fadeOut(){
	for(int x = 255; x >= 0; x = x - 15){
		gfxFadeScreen(GFX_BOTTOM, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_RIGHT, x);
		renderDebug();
		gfxFlushBuffers(); 
		gfxSwapBuffers();
		gspWaitForVBlank();
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
        drawFillRect( 0,getOnScreenY(y), 320,239, 255,/*y/(float)VSTY**/255,255, screen.screenBottom);
		
		//Button
		int x =  getOnScreenY(y)+(APPLICATION_ENTRY_H/4)*3 < 239 ? getOnScreenY(y)+(APPLICATION_ENTRY_H/4)*3 : 239;
		butX2 = x;
		int z = getOnScreenY(y) + APPLICATION_ENTRY_H/4 < 239 ? getOnScreenY(y) + APPLICATION_ENTRY_H/4 : 239;
		butX = z;
        drawFillRect( 200, z, 302,x, 0,148,255, screen.screenBottom);
    }
    else if(getOnScreenY(y)<0)
    {
        drawLine(0,0,320,0,0,255,0, screen.screenBottom);
        drawFillRect( 0,0, 320,getOnScreenY(y)+APPLICATION_ENTRY_H, 255,/*y/(float)VSTY**/255,255, screen.screenBottom);
        drawLine( 0, getOnScreenY(y) + APPLICATION_ENTRY_H -1 , 320, getOnScreenY(y) + APPLICATION_ENTRY_H -1, 224,224,224, screen.screenBottom);
		
		//Button
		butY = getOnScreenY(y) + APPLICATION_ENTRY_H/4 -1;
		butY2 = getOnScreenY(y)+(APPLICATION_ENTRY_H/4)*3 -1;
		drawFillRect( 200,butY, 302,butY2, 0,148,255, screen.screenBottom);
    }
    else{
        drawFillRect( 0,getOnScreenY(y), 320,getOnScreenY(y)+APPLICATION_ENTRY_H, 255,/*y/(float)VSTY**/255,255, screen.screenBottom);
        drawLine( 0, getOnScreenY(y) + APPLICATION_ENTRY_H -1 , 320, getOnScreenY(y) + APPLICATION_ENTRY_H -1, 224,224,224, screen.screenBottom);
		
		//Button
		butY = getOnScreenY(y)+APPLICATION_ENTRY_H/4;
		butY2 = getOnScreenY(y)+(APPLICATION_ENTRY_H/4)*3;
		drawFillRect( 200,butY, 302,butY2, 0,148,255, screen.screenBottom); //H: 36
    }
	
    gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackHeader, (char*)app.name.c_str(),240-getOnScreenY( APPTITLE_MARGIN + y ), 5);
    gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackSubHeader, (char*)app.version.c_str(),240-getOnScreenY( APPVERSION_MARGIN + y ), 5);
	int tl = 240 - getOnScreenY(APPVERSION_MARGIN + y);
	if (app.installed && !app.updateAvalible) {
		gfxDrawSprite(GFX_BOTTOM, GFX_LEFT, (u8*)Installed_bin, 18, 18, tl, (18 * 4));
	}
	else if (app.installed && app.updateAvalible) {
		gfxDrawSprite(GFX_BOTTOM, GFX_LEFT, (u8*)Update_bin, 18, 18, tl, (18 * 4));
	}
	else if (app.error) {
		//gfxDrawSprite(GFX_BOTTOM, GFX_LEFT, (u8*)Error_bin, 18, 18, tl, (18 * 4));
	}
	//Button
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhiteHeader, "More Info",240-getOnScreenY( ((APPLICATION_ENTRY_H/4)*2 + fontWhiteHeader.height/2) + y ), 212);
	
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

void background(){
	drawFillRect( 0, 0, 320, 240, 227,242,253, screen.screenBottom);
	drawFillRect( 0, 0, 399, 240, 227,242,253, screen.screenTopLeft);
	drawFillRect( 0, 0, 399, 240, 227,242,253, screen.screenTopRight);
}
void setStoreFrontImg(char* url){
	if (settings.internetConnection) {
		//w: 400
		//h: 192
		print("Downloading banner...\n");
		char* temp;
		u32 size;
		downloadFile(url, &temp, &size);
		cimg = (u8*)temp;
		print("Banner downloaded!\n");
	}
	if((char)cimg[0] == 'e' || !settings.internetConnection){
		//Set banner to offline banner
		printf("Failed to dowload and set banner, defaulting to offline one\n");
		cimg = (u8*) offline_bin;
	}
}
void drawTopBar(){
	drawFillRect(0,0,399,NAVBAR_H, 0,126,216, screen.screenTopLeft);
	drawFillRect(0,0,399,NAVBAR_H, 0,126,216, screen.screenTopRight);
	drawFillRect(0,12,399,SECONDARY_NAVBAR_H + 12, 0,148,255, screen.screenTopLeft);
	drawFillRect(0,12,399,SECONDARY_NAVBAR_H + 12, 0,148,255, screen.screenTopRight);

	snprintf(buffer,256, (char*)navbar.Title.c_str());
	gfxDrawText(GFX_TOP, GFX_LEFT, &fontWhiteHeader, buffer, 240 - (((SECONDARY_NAVBAR_H / 2) + fontWhiteHeader.height)), 13);
	gfxDrawText(GFX_TOP, GFX_RIGHT, &fontWhiteHeader, buffer, 240 - (((SECONDARY_NAVBAR_H / 2) + fontWhiteHeader.height)), 13);
	
#ifdef DEBUG
	snprintf(buffer, 256, "%s(%s), FPS: %d", APPLICATION_NAME, settings.version.c_str(), FPS);
#else
	snprintf(buffer, 256, "%s(%s)", APPLICATION_NAME, settings.version.c_str());
#endif
	drawString(buffer, (400-strlen(buffer)*8)/2,2, 255,255,255, screen.screenTopLeft,GFX_TOP);
	drawString(buffer, (400-strlen(buffer)*8)/2,2, 255,255,255, screen.screenTopRight,GFX_TOP);
	
	u64 timeInSeconds = osGetTime() / 1000; 
	u64 dayTime = timeInSeconds % SECONDS_IN_DAY; 
	snprintf(buffer,256, "%02llu:%02llu:%02llu",dayTime / SECONDS_IN_HOUR,(dayTime % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE,dayTime % SECONDS_IN_MINUTE);
	drawString(buffer, 315,2, 255,255,255, screen.screenTopLeft,GFX_TOP);
	drawString(buffer, 315,2, 255,255,255, screen.screenTopRight,GFX_TOP);
}

void drawCategory(Category_s cat, int place, bool subCategory /* Not implemented */) {

	int y = 0;
	int butY = 0, butY2 = 0, butX2 = 302, butX = 200;
	if (place == 1) {
		VSTY = CATEGORY_ENTRY_H;
		clearVButtons();
	}
	else {
		VSTY += CATEGORY_ENTRY_H;
	}

	y = (MARGIN * (place)) + (CATEGORY_ENTRY_H * (place - 1));

	if ((getOnScreenY(y) >= 240 || getOnScreenY(y) + CATEGORY_ENTRY_H <= 0) || VSPY >= VSTY) {
		butPos = 0;
		return; //Outside screen dont draw
	}
	else if (getOnScreenY(y) + CATEGORY_ENTRY_H >= 240)/*The entry is partly offscreen*/
	{

		//Button
		int x = getOnScreenY(y) + (CATEGORY_ENTRY_H / 4) * 3 < 239 ? getOnScreenY(y) + (CATEGORY_ENTRY_H / 4) * 3 : 239;
		butX2 = x;
		int z = getOnScreenY(y) + CATEGORY_ENTRY_H / 4 < 239 ? getOnScreenY(y) + CATEGORY_ENTRY_H / 4 : 239;
		butX = z;
	}
	else if (getOnScreenY(y)<0)
	{
		//Button
		butY = getOnScreenY(y) + CATEGORY_ENTRY_H / 4 - 1;
		butY2 = getOnScreenY(y) + (CATEGORY_ENTRY_H / 4) * 3 - 1;
	}
	else {
		//Button
		butY = getOnScreenY(y) + CATEGORY_ENTRY_H / 4;
		butY2 = getOnScreenY(y) + (CATEGORY_ENTRY_H / 4) * 3;
	}

	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlackHeader, (char*)cat.name.c_str(), 240 - getOnScreenY(24 + y), 5);
	clearVButtons();
	vButton_s but;
	but.ID = butPos;
	but.x = butX;
	but.y = butY;
	but.x2 = butX2;
	but.y2 = butY2;
	but.menu = 2;
	but.name = cat.name;
	addVButton(but);
	butPos++;
}

/* --- UI ELEMENTS --- */

Result guiPopup(char* title, char* content, char* b1, char* b2, u8* screen) {
	drawFillRect(34,58,274,191, 0,0,0, screen);			//Prints the Border
	drawFillRect(36,60,272,85, 0,126,216, screen);		//Prints the Body
	drawFillRect(36,85,272,189, 227,242,253, screen);	//Prints the TopBar
	/* Draw content */
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhite, title, 160, 240 - 16 * 12);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontBlack, content, 130, 240 - 16 * 12);
	/* Draw button(s) */
	drawFillRect(50,151,141,179, 46,204,113, screen);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhite, b1, 70, 240 - 16 * 11);
	if (b2 != NULL)
	{
		drawFillRect(166,151,257,179, 192,192,192, screen);
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, &fontWhite, b2, 70, (240 - 16 * 4) + 5);
	}
	return 0;
}

Result guiScrollbar(int x, int y, int x2, int y2, int procent) {
	return -99;
}


/* --- DEBUG --- */
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

void renderDebug() {
	/*int i = countLines(superStr);
	while (i>200 / fontDefault.height - 3) { cutLine(superStr); i--; }
	gfxDrawText(GFX_TOP, GFX_LEFT, &debugfnt, superStr, (240 - fontDefault.height * 5) + 6, 6);
	gfxDrawText(GFX_TOP, GFX_RIGHT, &debugfnt, superStr, (240 - fontDefault.height * 5) + 6, 6);*/
}

void renderDebugLog() {
#ifdef DEBUG //ToDo: move into an separate debug.h file.
	/*for (int x = 0; x <= 1; x++) {
		screen.screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
		screen.screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
		screen.screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
		renderDebug();
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}*/
#endif
}
