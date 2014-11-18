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
	system("cls");
	switch(CurrentMenu){
		case 0: //Main Menu
			mainMenu(input);
			break;
		case 1: //App Menu
			break;
		default:
			break;
	}
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