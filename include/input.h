#ifndef __INPUT_H__
#define __INPUT_H__

#include <iostream>

using namespace std;

struct Input_s{
	bool Up, Down, Left, Right, A, B, X, Y, Start, Select;
	u32 lX, lY, rX, rY;
};

void UpdateInput(Input_s*  input);
void resetInput(Input_s*  input);

#endif