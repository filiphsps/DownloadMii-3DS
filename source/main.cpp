#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
//Custom Classes
#include "utils.h"
#include "application.h"
#include "gui.h"
#include "input.h"
#include "download.h"
#include "font.h"
#include "splash.h"
#include "json.h"
#include "dataHandler.h"

using namespace std;

Input_s Input;
char superStr[8192];
char* jsonSS;

int main(int argc, char** argv)
{
	//Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	fsInit();
	sdmcInit();
	initGUI();
	//gfxSet3D(true);
	
    gspWaitForVBlank(); //wait to let the app register itself

	doSplash(); //SplashScreen
	
	Result r = networkInit();
	if(r != 0){
		print("networkInit: Error!\n");
	}
	Application_s app = {"NULL", "DownloadMii", "filfat Studio's", "1.0.0.0", "Download Homebrew apps on your 3ds", "Utils", "Stores", "NULL", "http://downloadmii.filfatstudios.com/stable/dmii.3dsx", "http://downloadmii.filfatstudios.com/stable/dmii.smdh", 5};
	r = installApp(app); //Test
	if(r != 0){
		print("installApp: Error!\n");
	}
	r = updateAppList(&overviewApps, "http://downloadmii.filfatstudios.com/testing/apps.json");
	if(r != 0){
		print("updateAppList: Error\n");
	}
	//APP_STATUS status;
	
	
	//Banner:
	setStoreFrontImg("http://downloadmii.filfatstudios.com/testing/banner1.bin");
	
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
	char buffer[110];
	while (aptMainLoop())
	{
		UpdateInput(&Input);
		if(Input.touchX != 0){
			sprintf(buffer, "%d,%d\n", Input.touchX, Input.touchY);
			print(buffer);
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
		renderGUI();
		if (Input.Start){
			print("Exiting..\n");
			renderGUI();
			break; //break in order to return to hbmenu
		} else if(Input.R && !(scene > maxScene)){
			scene++;
		} else if(Input.L && (scene - 1 >= 0)){
			scene--;
		}
		if(Input.Down){
			if(!(VSPY + 1 >= VSTY))
				VSPY += 1;
			else
				VSPY = VSTY;
		}
		else if(Input.Up){
			if(!(VSPY - 1 <= 0))
				VSPY -= 1;
			else
				VSPY = 0;
		}
		
		//VSPY += 1;
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
