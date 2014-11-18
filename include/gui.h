#ifndef __GUI_H__
#define __GUI_H__

#include <iostream>
#include "input.h"

using namespace std;

static volatile int CurrentMenu;
static volatile int PointerPos;
static volatile int NApps;

void initGUI();
void renderGUI(Input_s* input);
void mainMenu(Input_s* input);
string generateMainMenu(int pointer, int apps);
#endif