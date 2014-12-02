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
	Application_s app = {1, 4, "Test3DS", "filfat", "Utils", "http://downloadmii.filfatstudios.com/Applications.json", "http://downloadmii.filfatstudios.com/Applications.json"};
	r = installApp(app); //Test
	if(r != 0){
		print("installApp: Error!\n");
	}
	
	//APP_STATUS status;
	
	//Fade into main loop, needs to get moved over to splash.cpp
	/*for(int x = 255; x >= 0; x = x - 15){
		gfxFadeScreen(GFX_BOTTOM, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_RIGHT, x);
		gfxFlushBuffers(); 
		gfxSwapBuffers();
	}
	renderGUI();*/
	/*for(int x = 0; x <= 255; x = x + 10){
		gfxFadeScreen(GFX_BOTTOM, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_RIGHT, x);
		gfxFlushBuffers(); 
		gfxSwapBuffers();
	}*/
	/* Main loop */
	unsigned int lastScene = 0;
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
					break;
				case 1:
					sceneTitle = "Top Downloaded Applications";
					break;
				case 2:
					sceneTitle = "Top Downloaded Games";
					break;
				default:
					sceneTitle = "Staff Pick";
					break;
			}
			lastScene = scene;
		}
		renderGUI();
		if (Input.Start){
			print("Exiting..\n");
			renderGUI();
			break; //break in order to return to hbmenu
		} else if(Input.R && (scene > maxScene)){
			scene++;
		} else if(Input.L && (scene < 0)){
			scene--;
		}
		if(Input.Down){
			if(!(VSPY + 5 >= VSTY))
				VSPY += 5;
			else
				VSPY = VSTY;
		}
		else if(Input.Down){
			if(!(VSPY - 5 <= 0))
				VSPY -= 5;
			else
				VSPY = 0;
		}
		
		//VSPY += 5;
		gspWaitForVBlank();
	}

	//Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}
