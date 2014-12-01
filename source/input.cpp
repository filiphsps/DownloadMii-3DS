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

void UpdateInput(Input_s* input){
	resetInput(input);
	hidTouchRead(&tp); 
	input->touchX = tp.px; 
 	input->touchY = tp.py; 

	hidScanInput();
	u32 kDown = hidKeysDown();
	switch(kDown){
		case KEY_A:
			input->A = true;
			break;
		case KEY_B:
			input->B = true;
			break;
		case KEY_X:
			input->X = true;
			break;
		case KEY_Y:
			input->Y = true;
			break;



		case KEY_UP:
			input->Up = true;
			print("Up\n");
			break;
		case KEY_DOWN:
			input->Down = true;
			print("Down\n");
			break;
		case KEY_LEFT:
			input->Left = true;
			print("Left\n");
			break;
		case KEY_RIGHT:
			input->Right = true;
			print("Right\n");
			break;



		case KEY_START:
			input->Start = true;
			break;
		case KEY_SELECT:
			input->Select = true;
			break;
		case KEY_L:
			input->L = true;
			break;
		case KEY_R:
			input->R = true;
			break;
		default:
			break;
	}
}

void resetInput(Input_s* input){
	input = {};
}
