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

using namespace std;
using namespace picojson;

Input_s Input;

void MainLoop();

int main()
{
	//Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	initGUI();
	//gfxSet3D(true); //uncomment if using stereoscopic 3D
	
	APP_STATUS status;
	
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
			//Flush and swap framebuffers
			gfxFlushBuffers();
			gfxSwapBuffers();
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
