#pragma once


#include <iostream>
#include <vector>

using namespace std;

struct Input_s{
	bool Up = false, Down = false, Left = false, Right = false, A = false, B = false, X = false, Y = false, Start = false, Select = false, L= false, R = false;
	u32 lX = 0, lY = 0, rX = 0, rY = 0; //ToDo
	u16 touchX = 0, touchY = 0;
};

struct vButton_s{
	int ID;
	int x, y, x2, y2;
	bool pressed;
};

extern vector<vButton_s> vButtons;

void UpdateInput(Input_s*  input);
void resetInput(Input_s*  input);


void checkVButtonTouch(Input_s* input); 
void addVButton(vButton_s button);
void clearVButtons();