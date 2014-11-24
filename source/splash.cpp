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
#include "background_bin.h"

using namespace std;

//extern char __BUILD_NUMBER;

void doSplash(){
	char buffer[110];
	sprintf(buffer, "DownloadMii Build %u", 5/*(unsigned long) &__BUILD_NUMBER*/);
	for(int x = 0;x <= 1; x++){
		screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); 
		screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
		screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL); 
		clearScreen(screenBottom, GFX_BOTTOM);
		clearScreen(screenTopLeft, GFX_TOP); 
		clearScreen(screenTopRight, GFX_TOP);
		
		//Temp img
		/*gfxDrawSprite(GFX_TOP, GFX_LEFT, (u8*)background_bin, 240, 400, 0, 0);
		gfxDrawSprite(GFX_TOP, GFX_RIGHT, (u8*)background_bin, 240, 400, 0, 0);
		gfxDrawSprite(GFX_BOTTOM, GFX_LEFT, (u8*)background_bin, 240, 320, 0, 0);*/
		
		drawFillRect( 0,0,400,240, 0,0,0, screenTopLeft);
		drawFillRect( 0,0,400, 240, 0,0,0, screenTopRight);
		drawFillRect( 0,0,320,240, 0,0,0, screenBottom);
		
		//Loading text
		gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 240-fontDefault.height*1, 2); 
		gfxDrawText(GFX_TOP, GFX_RIGHT, NULL, buffer, 240-fontDefault.height*1, 2);
		gfxDrawText(GFX_TOP, GFX_LEFT, NULL, "Loading...", 240-fontDefault.height*2, 2); 
		gfxDrawText(GFX_TOP, GFX_RIGHT, NULL, "Loading...", 240-fontDefault.height*2, 2);
		
		gfxFlushBuffers(); 
		gfxSwapBuffers();
	}
}
