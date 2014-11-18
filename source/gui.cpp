#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include "utils.h"
#include "application.h"
#include "input.h"
#include "gui.h"

using namespace std;

void initGUI(){
	CurrentMenu = 0;
	PointerPos = 0;
	NApps = 43 /*Temp number*/;
}

void renderGUI(Input_s* input){
	cls();
	switch(CurrentMenu){
		case 0: //Main Menu
			mainMenu(input);
			break;
		case 1: //App Menu
			break;
		default:
			break;
	}
	render_gfx();
}

void mainMenu(Input_s* input){
	
	//Pointer navigation
	if(input->Up){
		PointerPos++;
	}
	else if(input->Down){
		PointerPos--;
	}
	
	//Check if PointerPos is less/higher than the number of applications
	if(PointerPos < 0){
		PointerPos = NApps;
	}
	else if(PointerPos > NApps){
		PointerPos = 0;
	}
	
	string Menu = generateMainMenu(PointerPos, NApps);
}

string generateMainMenu(int pointer, int apps){
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

void printString(string text, int x, int y){
	/*char buffer[100];
	sprintf(buffer, "%s", text);
	drawString(buffer, x, y, 255, 255, 255, screenTopLeft, GFX_LEFT);
	drawString(buffer, x, y, 255, 255, 255, screenTopRight, GFX_LEFT);
	drawString(buffer, x, y, 255, 255, 255, screenBottom, GFX_BOTTOM);*/
}
 
void render_gfx(){
	/*gfxFlushBuffers();
	gfxSwapBuffers();
	screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL);
	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);*/
}

void cls(){
/*	screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL);
	clearScreen(screenBottom, GFX_BOTTOM);
	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	clearScreen(screenTopLeft, GFX_LEFT);
	clearScreen(screenTopRight, GFX_LEFT); */
}