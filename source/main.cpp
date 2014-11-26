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
	initGUI();
	//gfxSet3D(true);
	
    gspWaitForVBlank(); //wait to let the app register itself

	doSplash(); //SplashScreen
	
	Result r = networkInit();
	if(r != 0){
		//Error,
		//ToDo: Set application in offline mode
		print("Error could not init network!\n");
	}
	else{
		print("Downloading File..\n");
		char* url = APPLICATIONSJSON; //Temp
		jsonSS = downloadFile(url);
		if(jsonSS != NULL && jsonSS[0] != 'e'){
			print("Success\n");
			print(jsonSS); //ToDo
			print("\n");
		}
		else{
			print(jsonSS); //Prints out the error
			jsonSS = offlineJson;
			print(", Offline mode enabled\n");
			
		}
	}
	
	//JSON TEST-----------------------------------------
	
	//--------------------------------------------------
	
	//APP_STATUS status;
	
	//Fade into main loop, needs to get moved over to splash.cpp
	for(int x = 255; x >= 0; x = x - 15){
		gfxFadeScreen(GFX_BOTTOM, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_RIGHT, x);
		gfxFlushBuffers(); 
		gfxSwapBuffers();
	}
	renderGUI();
	/*for(int x = 0; x <= 255; x = x + 10){
		gfxFadeScreen(GFX_BOTTOM, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_LEFT, x);
		gfxFadeScreen(GFX_TOP, GFX_RIGHT, x);
		gfxFlushBuffers(); 
		gfxSwapBuffers();
	}*/
	/* Main loop */
	unsigned int lastScene = 0;
	while (aptMainLoop())
	{
		UpdateInput(&Input);
		
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
		
		
		gspWaitForVBlank();
	}

	//Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}
