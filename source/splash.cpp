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
#include "main.h"
#include "splash_bin.h"

using namespace std;

//extern char __BUILD_NUMBER;

void doSplash(){
	char buffer[256];
	snprintf(buffer,256, "DownloadMii Build: %s\n", __DATE__);
	//Loading text
	print(buffer);
	print("Loading...\n");
	for(int x = 0;x <= 1; x++){
		screen.screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); 
		screen.screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
		screen.screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
		
		//Temp img
		gfxDrawSprite(GFX_TOP, GFX_LEFT, (u8*)splash_bin, 240, 400, 0, 0);
		gfxDrawSprite(GFX_TOP, GFX_RIGHT, (u8*)splash_bin, 240, 400, 0, 0);

		renderDebug();
		
		gfxFlushBuffers(); 
		gfxSwapBuffers();
	}
}
