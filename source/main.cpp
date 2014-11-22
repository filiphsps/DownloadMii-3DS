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
//#include "json.h"
#include "download.h"

using namespace std;
//using namespace picojson;

Input_s Input;

void MainLoop();

int main(int argc, char** argv)
{
	//Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	initGUI();
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, "networkInit()\n", 240-fontDefault.height*1, 10);
	Result r = networkInit();
	if(r != 0){
		//Error,
		//ToDo: Set application in offline mode
		gfxDrawText(GFX_TOP, GFX_LEFT, NULL, "Error could not init network!\n", 240-fontDefault.height*1, 10);
	}
	else{
		gfxDrawText(GFX_TOP, GFX_LEFT, NULL, "Downloading File..\n", 240-fontDefault.height*2, 10);
		char* url = "http://downloadmii.filfatstudios.com/applications.json";
		char* jsonSS = downloadFile(url);
		if(jsonSS != NULL){
			gfxDrawText(GFX_TOP, GFX_LEFT, NULL, "Success\n", 240-fontDefault.height*3, 10);
			debug(jsonSS); //ToDo
		}
		else{
			gfxDrawText(GFX_TOP, GFX_LEFT, NULL, "Error\n", 240-fontDefault.height*3, 10);
			debug("");
		}	
	}
	
	//gfxSet3D(true); //uncomment if using stereoscopic 3D
	
	APP_STATUS status;
	
	/* Main loop */
	while (aptMainLoop())
	{
		MainLoop();
		if (Input.Start == true){
			gfxDrawText(GFX_TOP, GFX_LEFT, NULL, "Exiting\n", 240-fontDefault.height*1, 10);
			break; //break in order to return to hbmenu
		}
	}

	//Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}

void MainLoop(){
	UpdateInput(&Input);
	renderGUI();
}
