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
#include "json.h"
#include "download.h"

using namespace std;
using namespace picojson;

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
	Result r = networkInit();
	if(r != 0){
		//Error,
		//ToDo: Set application in offline mode
	}
	//gfxSet3D(true); //uncomment if using stereoscopic 3D
	
	APP_STATUS status;
	
	//Test
	string url = "http://downloadmii.filfatstudios.com/applications.json";
	string jsonSS = downloadFile(url);
	jsonSS.resize(20);
	debug(jsonSS);
	
	/* Main loop */
	while ((status = aptGetStatus()) != APP_EXITING)
	{
		if (status == APP_RUNNING)
		{
			//If the app is currently in the forground running, execute the program.
			gspWaitForVBlank();
			MainLoop();
			if (Input.Start == true){
				break; //break in order to return to hbmenu
			}
		}
		else if (status == APP_SUSPENDING)
		{
			//If the app is currently suspended in the background, return to the home menu.
			break;
		}
		else if (status == APP_SLEEPMODE)
		{
			//If the app is currently suspended in sleep mode, wait.
			aptWaitStatusEvent();
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
