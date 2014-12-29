#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
//Custom Classes
#include "main.h"
#include "utils.h"
#include "application.h"
#include "gui.h"
#include "input.h"
#include "download.h"
#include "font.h"
#include "splash.h"
#include "dataHandler.h"
#include "settings.h"
#include "music.h"

using namespace std;

Input_s Input;
char superStr[9192];
char* jsonSS;

int currentMenu = 0;

//Todo:
Application_s currentApp/* = {"NULL", "Error", "App isn't loaded", "E.RR.O.R", "Please restart your 3DS and try again!", "Error", "Error", "NULL", "http://downloadmii.filfatstudios.com/testing/test.3dsx", "http://downloadmii.filfatstudios.com/testing/test.3dsx", 5, true, false}*/;

static int CalcFPS(); //ToDo: move to utils.cpp
char* getVersion();

int main(int argc, char** argv)
{
	//Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	fsInit();
	sdmcInit();
	guiInit();
	settingsInit(DEFAULT_SETTINGS_PATH);
	//gfxSet3D(true);
	
    gspWaitForVBlank(); //wait to let the app register itself

	doSplash(); //Splash Screen
	
	Result r = networkInit();
	if(r != 0){
		print("networkInit: Error!\n");
	}
	
	u8 isN3DS=0;
	APT_CheckNew3DS(NULL, &isN3DS);
	if(isN3DS){
		aptOpenSession();
		r = APT_SetAppCpuTimeLimit(NULL, 80);
		if(r != 0){
			print("APT_SetAppCpuTimeLimit: Error\n");
		}
		aptCloseSession();
	}
	else {
		aptOpenSession();
		r = APT_SetAppCpuTimeLimit(NULL, 30);
		if (r != 0) {
			print("APT_SetAppCpuTimeLimit: Error\n");
		}
		aptCloseSession();
	}
	for (int x = 0; x <= 1; x++) {
			screen.screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
			screen.screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
			screen.screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
			renderDebug();
			gfxFlushBuffers();
			gfxSwapBuffers();
			gspWaitForVBlank();
	}
	r = doListUpdate();
	if (r != 0) {
		print("doUpdate: Error\n");
	}

	//APP_STATUS status;
	
	//gfxSetDoubleBuffering(false);
	
	/* Threading */
	/*Handle threadHandle;
	u32 *stack = (u32*)malloc(0x4000);
	svcCreateThread(&threadHandle, secondThread, 0, &stack[0x4000>>2], 0x3F, 0);*/

	fadeOut();
	debugfnt = fontBlack;

	/* Main loop */
	int lastScene = 0;
	int lastMenu = -1;
	char buffer[256];
	r = checkUpdate(getVersion()); //ToDo: use settings.ini
	if (r == 0) goto EXIT;
	while (aptMainLoop())
	{
		loopStart:
		#ifdef DEBUG
		FPS = CalcFPS();
		#endif
		UpdateInput(&Input);
		
		switch(currentMenu){
			case 0: //Overview
				if(Input.R && !(scene > maxScene)){
					scene++;
				} else if(Input.L && (scene - 1 >= 0)){
					scene--;
				} else if(hidKeysHeld() & KEY_DOWN){
					if(!(VSPY + 5 > VSTY - 240))
						VSPY += 5;
					else{
						VSPY = VSTY - 240;
						//ToDo: Indicator that we have hit the end of the list
					}
				} else if(hidKeysHeld() & KEY_UP){
					if(!(VSPY - 5 <= 0))
						VSPY -= 5;
					else{
						VSPY = 0;
						//ToDo: Indicator that we have hit the start of the list
					}
				}
				//Loop through all the buttons
				for(auto &but : vButtons){
					if(but.pressed){
						currentApp = but.app;
						currentMenu = but.menu;
					}
				}
				if(lastScene != scene){
					switch(scene){
						case 0:
							sceneTitle = "Overview";
							setStoreFrontImg("http://downloadmii.filfatstudios.com/banner.bin");
							setAppList(overviewApps);
							break;
						case 1:
							sceneTitle = "Top Downloaded Applications";
							setAppList(topApps);
							break;
						case 2:
							sceneTitle = "Top Downloaded Games";
							setAppList(topGames);
							break;
						case 3:
							sceneTitle = "Staff Pick";
							setAppList(staffSelectApps);
							break;
						default:
							scene = 0;
					}
					lastScene = scene;
				}
				break;
			case 1: //Settings
				if(lastMenu != currentMenu)
					sceneTitle = "Settings";
				break;
			case 2: //App Page
				if(lastMenu != currentMenu){
					sceneTitle = (char*)currentApp.name.c_str();
					//setStoreFrontImg(currentApp.background);
				}
				if (Input.B) {
					currentMenu = 0;
				}
				for (auto &but : vButtons) {
					if ((but.pressed && but.ID == 0) || Input.A) { //Download
						clearVButtons();
						currentMenu = 3;
						installApp(currentApp);
						goto loopStart;
					}
					else if (but.pressed && but.ID == 1){ //Publisher
						clearVButtons();
						currentMenu = 4;
						goto loopStart;
					}
				}
				break;
			case 3: //Downloads
				if(lastMenu != currentMenu)
					sceneTitle = "Downloads";
				if (Input.B) {
					currentMenu = 0;
				}
				break;
			case 4: //by dev
				if (lastMenu != currentMenu){
					snprintf(buffer,256, "Applications By %s\n", currentApp.publisher.c_str());
					sceneTitle = (char*)buffer;
					r = updateDevList(&devList, (char*)currentApp.publisher.c_str());
					setAppList(devList);
				}
				break;
			default:
				currentMenu = 0;
				break;
		}
		if (lastMenu != currentMenu) {
			clearVButtons();
			lastScene = -1;
			lastMenu = currentMenu;
		}
		gspWaitForVBlank();
		renderGUI();
		/* In case of start, exit the app */
		if (Input.Start){
			print("Exiting..\n");
			break;
		}
	}
	//Exit services
	EXIT:
	fsExit();
	sdmcExit();
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}

char* getVersion() {
	char buffer[256];
	snprintf(buffer, 256, "/%s/%s", HBPATH, "downloadmii");
	FILE *fp = fopen(buffer, "r+");
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *string = (char*)malloc(fsize + 1);
	fread(string, fsize, 1, fp);
	fclose(fp);

	if (string[1] != '.')
		string = "0.0.0.0";
	//ToDo
	return string;
}

static int CalcFPS(){
	static int FC = 0;
	static u32 lt;
	u32 ClockSpeed = osGetTime();
	static int FPS;
	
	FC++;
	if(ClockSpeed - lt > 1000){
		lt = ClockSpeed;
		FPS = FC;
		FC = 0;
	}
	return FPS;
}
