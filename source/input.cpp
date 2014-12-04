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

touchPosition tp;
int x;
void UpdateInput(Input_s* input){
	resetInput(input);
	hidTouchRead(&tp); 
	input->touchX = tp.px; 
 	input->touchY = tp.py; 

	hidScanInput();
	u32 kDown = hidKeysDown();
	u32 kHeld = hidKeysHeld();
	if(kDown){
		x++;
		char buffer[100];
		sprintf(buffer, "Input, %d\n", x);
		print(buffer);
		if(kDown & KEY_A){
			input->A = true;
		} if(kDown & KEY_B){
			input->B = true;
		} if(kDown & KEY_X){
			input->X = true;
		} if(kDown & KEY_Y){
			input->Y = true;
		}
		
		if(kDown & KEY_UP){
			input->Up = true;
		} if(kDown & KEY_DOWN){
			input->Down = true;
		} if(kDown & KEY_LEFT){
			input->Left = true;
		} if(kDown & KEY_RIGHT){
			input->Right = true;
		}
		
		if(kDown & KEY_START){
			input->Start = true;
		} if(kDown & KEY_SELECT){
			input->Select = true;
		} if(kDown & KEY_L){
			input->L = true;
		} if(kDown & KEY_R){
			input->R = true;
		}
	}
}

void resetInput(Input_s* input){
	input->A = false;
	input->B = false;
	input->X = false;
	input->Y = false;
	input->Up = false;
	input->Down = false;
	input->Left = false;
	input->Right = false;
	input->Start = false;
	input->Select = false;
	input->L = false;
	input->R = false;
}
