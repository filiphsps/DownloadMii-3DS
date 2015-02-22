#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <3ds.h>
#include "print.h"
#include "main.h"

#ifdef DEBUG
static int started = 0;
static FILE *fdebug = NULL;
#endif

s32 printInit(const char *fileName) {
#ifdef DEBUG
	started = 0;
	remove(fileName);
	fdebug = fopen(fileName, "wb");
	if (fdebug) started = 1;
	return started;
#endif
	return 0;
}

#ifdef DEBUG
void printExit(void) {
	if (fdebug) fclose(fdebug);
	fdebug = NULL;
	started = 0;
	return;
}

void print(const char *text, ...) {
	if (!started || text == NULL) return;

	va_list argp;
	va_start(argp, text);
	if (fdebug) {
		vfprintf(fdebug, text, argp);
		fprintf(fdebug, "\r\n");
		fflush(fdebug);
	}
	//snprintf(&superStr[strlen(superStr)], 9192, text, argp);
	svcOutputDebugString(superStr, 9192);
	va_end(argp);
}
#endif