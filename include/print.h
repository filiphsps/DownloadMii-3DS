/*------------------------------------------------------
DownloadMii
© Filiph Sandström 2014-2015

TODO:
* Rename files to "debug.h" and "debug.cpp"

CONTRIBUTORS:
* Filiph Sandström (filfat) - Modified code
* Joostin - Orginal code
------------------------------------------------------*/
#pragma once
#include <3ds.h>
#include "main.h"

extern char superStr[];

s32 printInit(const char *fn);
#ifdef DEBUG
	void printExit(void);
	void print(const char *text, ...);

#else

#define DebugStop()
#define print(...) snprintf(&superStr[strlen(superStr)], 9192, __VA_ARGS__); svcOutputDebugString(superStr, 9192);

#endif