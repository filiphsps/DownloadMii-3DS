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
#include "font.h"

using namespace std;
using namespace picojson;

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
	
	Result r = networkInit();
	if(r != 0){
		//Error,
		//ToDo: Set application in offline mode
		print("Error could not init network!\n");
	}
	else{
		print("Downloading File..\n");
		char* url = "http://downloadmii.filfatstudios.com/applications.json";
		jsonSS = downloadFile(url);
		if(jsonSS != NULL && jsonSS[0] != 'e'){
			print("Success\n");
			print(jsonSS); //ToDo
			print("\n");
		}
		else{
			print(jsonSS); //Prints out the error
			print(", Offline mode enabled\n");
			jsonSS = "{\"Apps\":{\"Tools\":[{\"name\":\"Temp\",\"owner\":\"Temp\",\"description\":\"Line 1\nLine 2\",\"subGen\":\"Theme\",\"downloadUrl\":\"http://exampke.com/temp.3dsx\",\"icon\":\"http://example.com/temp.png\",\"smdh\":\"http://example.com/temp.smdh\"},{\"name\":\"Temp2\",\"owner\":\"Temp\",\"description\":\"Line 1\nLine 2\",\"subGen\":\"Theme\",\"downloadUrl\":\"http://exampke.com/temp.3dsx\",\"icon\":\"http://example.com/temp.png\",\"smdh\":\"http://example.com/temp.smdh\"}],\"Games\":[{\"name\":\"Pong\",\"owner\":\"Temp\",\"description\":\"Line 1\nLine 2\",\"subGen\":\"Retro\",\"downloadUrl\":\"http://exampke.com/pong.3dsx\",\"icon\":\"http://example.com/pong.png\",\"smdh\":\"http://example.com/pong.smdh\"}]}}";
		}
	}
	
	//JSON TEST-----------------------------------------
	//Link to example: http://developer.mbed.org/users/mimil/code/PicoJSONSample/docs/81c978de0e2b/main_8cpp_source.html
		picojson::value v;
		
		char * json = (char*) malloc(strlen(jsonSS)+1);
		strcpy(json, jsonSS);
		string err = picojson::parse(v, json, json + strlen(json));
		print(err.c_str());
		print("\n");
		
		const picojson::array& a = v.get("Apps").get("Tools").get<picojson::array>();
		
		
		for (picojson::array::const_iterator i = a.begin(); i != a.end(); ++i) { 
			print((*i).get("name").get<string>().c_str());
			print("\n");
		} 

		
	//--------------------------------------------------
	
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