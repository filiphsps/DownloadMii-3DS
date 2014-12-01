#pragma once


#include <iostream>

using namespace std;

struct Input_s{
	bool Up = false, Down = false, Left = false, Right = false, A = false, B = false, X = false, Y = false, Start = false, Select = false, L= false, R = false;
	u32 lX = 0, lY = 0, rX = 0, rY = 0; //ToDo
	u16 touchX = 0, touchY = 0;
};

void UpdateInput(Input_s*  input);
void resetInput(Input_s*  input);