#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>

using namespace std;

struct Application_s{
	int id;
	string Name;
	string Owner;
	//TODO
	
};

string generateMenu(int pointer, int apps);
Application_s getApp(int id);
Application_s defineApplication_s(int id, string name);

int main()
{
	//Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	//gfxSet3D(true); //uncomment if using stereoscopic 3D

	/* Main loop */
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		/*
			Main Code
		*/
			generateMenu(3, 46);
		//---------------------------
		
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; //break in order to return to hbmenu

		//Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	//Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}

string generateMenu(int pointer, int apps){
	string output = "";
	Application_s ta;
	for(int x = 0; x <= apps; x++){
		if(x == pointer)
			output += ">"; //Render pointer
		ta = getApp(x);
		output += ta.Name;
	}
	return output;
}

Application_s getApp(int id){
	ostringstream convert;
	convert << "App " << id;
	Application_s test = defineApplication_s(id, convert.str());
	return test;
}

Application_s defineApplication_s(int id, string name){
	Application_s App;
	App.id = id;
	App.Name = name;
	App.Owner = "Test";
	return App;
}