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
#include "json.h"
#include "dataHandler.h"
#include "settings.h"

using namespace std;

Input_s Input;
char superStr[8192];
char* jsonSS;

int currentMenu = 0;
Application_s currentApp = {"NULL", "DownloadMii", "filfat Studio's", "1.0.0.0", "Download Homebrew apps on your 3ds", "Utils", "Stores", "NULL", "http://downloadmii.filfatstudios.com/stable/dmii.3dsx", "http://downloadmii.filfatstudios.com/stable/dmii.smdh", 5};

int main(int argc, char** argv)
{
	//Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	sdmcInit();
	fsInit();
	guiInit();
	settingsInit(DEFAULT_SETTINGS_PATH);
	//gfxSet3D(true);
	
    gspWaitForVBlank(); //wait to let the app register itself

	doSplash(); //SplashScreen
	
	Result r = networkInit();
	if(r != 0){
		print("networkInit: Error!\n");
	}
	
	r = updateAppList(&overviewApps, "http://downloadmii.filfatstudios.com/testing/apps.json");
	if(r != 0){
		print("updateAppList: Error\n");
	}
	//APP_STATUS status;
	
	//Fade into main loop, needs to get moved over to splash.cpp
	for(int x = 255; x >= 0; x = x - 15){
		gfxFadeScreen(GFX_BOTTOM, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_RIGHT, x);
		gfxFlushBuffers(); 
		gfxSwapBuffers();
	}
	/* Main loop */
	unsigned int lastScene = -1;
	int lastMenu = -1;
	char buffer[110];
	while (aptMainLoop())
	{
		UpdateInput(&Input);
		switch(currentMenu){
			case 0: //Overview
				if(lastMenu != currentMenu)
					sceneTitle = "Overview";
				if(Input.R && !(scene > maxScene)){
					scene++;
				} else if(Input.L && (scene - 1 >= 0)){
					scene--;
				} else if(hidKeysHeld() & KEY_DOWN){
					if(!((VSPY) + 5 >= VSTY))
						VSPY += 5;
					else
						VSPY = VSTY;
				} else if(hidKeysHeld() & KEY_UP){
					if(!(VSPY - 5 <= 0))
						VSPY -= 5;
					else
						VSPY = 0;
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
					setStoreFrontImg("http://downloadmii.filfatstudios.com/assets/logo.bin");
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
			lastScene = -1;
			lastMenu = currentMenu;
		}
		
		if(Input.touchX != 0){
			sprintf(buffer, "%d,%d\n", Input.touchX, Input.touchY);
			print(buffer);
		}
		if(Input.A){
			currentMenu++;
		}
		/* In case of start, exit the app */
		if (Input.Start){
			print("Exiting..\n");
			break;
		}
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
