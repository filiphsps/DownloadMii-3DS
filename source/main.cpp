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
#include "font.h"

using namespace std;
//using namespace picojson;

Input_s Input;
char superStr[8192];
void MainLoop();

int main(int argc, char** argv)
{
	//Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	initGUI();
	//gfxSet3D(true);
	Result r = networkInit();
	if(r != 0){
		//Error,
		//ToDo: Set application in offline mode
		print("Error could not init network!\n");
	}
	else{
		print("Downloading File..\n");
		char* url = "http://downloadmii.filfatstudios.com/applications.json";
		char* jsonSS = downloadFile(url);
		if(jsonSS != NULL && jsonSS[0] != 'e'){
			print("Success\n");
			print(jsonSS); //ToDo
		}
		else{
			print(jsonSS); //Prints out the error
		}
		print("\n");
	}
	//APP_STATUS status;
	
	/* Main loop */
	while (aptMainLoop())
	{
		UpdateInput(&Input);
		renderGUI();
		if (Input.Start){
			print("Exiting\n");
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