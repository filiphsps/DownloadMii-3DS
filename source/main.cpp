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
char superStr[8192];
char* jsonSS;

int currentMenu = 0;

//Todo:
Application_s currentApp = {"NULL", "DownloadMii", "filfat Studio's", "1.0.0.0", "Download Homebrew apps on your 3ds", "Utils", "Stores", "NULL", "http://downloadmii.filfatstudios.com/stable/dmii.3dsx", "http://downloadmii.filfatstudios.com/stable/dmii.smdh", 5};

static int CalcFPS(); //ToDo: move to utils.cpp

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
	
	//ToDo: check if we are running on o3ds or n3ds
	/*aptOpenSession();
	r = APT_SetAppCpuTimeLimit(NULL, (u32)80);
	if(r != 0){
		print("APT_SetAppCpuTimeLimit: Error\n");
	}
	aptCloseSession();*/
	
	r = doListUpdate();
	if(r != 0){
		print("doUpdate: Error\n");
	}
	//APP_STATUS status;
	
	/* Threading */
	/*Handle threadHandle;
	u32 *stack = (u32*)malloc(0x4000);
	svcCreateThread(&threadHandle, secondThread, 0, &stack[0x4000>>2], 0x3F, 0);*/
	
	fadeOut();
	/* Main loop */
	unsigned int lastScene = -1;
	int lastMenu = 0;
	while (aptMainLoop())
	{
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
							setStoreFrontImg("http://downloadmii.filfatstudios.com/testing/banner1.bin"); //Test
							setAppList(&overviewApps);
							break;
						case 1:
							sceneTitle = "Top Downloaded Applications";
							setStoreFrontImg("http://downloadmii.filfatstudios.com/testing/banner2.bin"); //Test
							setAppList(&topApps);
							break;
						case 2:
							sceneTitle = "Top Downloaded Games";
							setAppList(&topGames);
							break;
						case 3:
							sceneTitle = "Staff Pick";
							setAppList(&staffSelectApps);
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
					sceneTitle = currentApp.name;
					//setStoreFrontImg("http://downloadmii.filfatstudios.com/assets/logo.bin");
					//setStoreFrontImg(currentApp.background);
				}
				break;
			case 3: //Downloads
				if(lastMenu != currentMenu)
					sceneTitle = "Downloads";
				break;
			case 4: //by dev
				if(lastMenu != currentMenu)
					sceneTitle = "By Developer <Devname>";
				break;
			default:
				currentMenu = 0;
				break;
		}
		renderGUI();
		if(lastMenu != currentMenu){
			clearVButtons();
			lastScene = -1;
			lastMenu = currentMenu;
			r = doListUpdate();
		}
		if(Input.A){
			currentMenu++;
		}
		/* In case of start, exit the app */
		if (Input.Start){
			print("Exiting..\n");
			break;
		}
		FPS = CalcFPS();
		gspWaitForVBlank();
	}

	//Exit services
	fsExit();
	sdmcExit();
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
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
