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

void UpdateInput(Input_s* input){
	resetInput(input);
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
			break;
		case KEY_DOWN:
			input->Down = true;
			break;
		case KEY_LEFT:
			input->Left = true;
			break;
		case KEY_RIGHT:
			input->Right = true;
			break;



		case KEY_START:
			input->Start = true;
			break;
		case KEY_SELECT:
			input->Select = true;
			break;
	}
}

void resetInput(Input_s* input){
	input = new Input_s;
}
