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
//#include "download.h"

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
	//Result r = networkInit();
	/*if(r != 0){
		//Error,
		//ToDo: Set application in offline mode
	}*/
	//gfxSet3D(true); //uncomment if using stereoscopic 3D
	
	//APP_STATUS status;
	
	//Test
	//char* url = "http://downloadmii.filfatstudios.com/applications.json";
	//char* jsonSS = downloadFile(url);
	/*if(jsonSS != NULL){
		debug(jsonSS);
	}
	else{
		debug("");
	}*/
	
	/* Main loop */
	while (aptMainLoop())
	{
		MainLoop();
		if (Input.Start == true){
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
