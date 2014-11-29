#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include "main.h"
#include "application.h"
#include "download.h"
#include "gui.h"
#include "file.h"

using namespace std;

Result installApp(Application_s app){
	//ToDo
	char buffer[110];
	FILE *fp;
	
	/* MKDIR */
	sprintf(buffer, "\%s\%s", HBPATH, app.name);
	mkdir(buffer, 0777);
	
	/* Download Files */
	char* file3dsx = downloadFile(app.execURL);
	char* filesmdh = downloadFile(app.smdhURL);
	if(file3dsx[0] == 'e' || filesmdh[0] == 'e') //Can return false positives(rare), needs to be fixed.
		return -1; //Error
	/* Save files to the SD-Card */
	//Start with the elf file
	sprintf(buffer, "\%s\%s\%s.3dsx", HBPATH, app.name, app.name);
	fp = fopen(buffer, "w+");
	fprintf(fp, file3dsx);
	fclose(fp);
	//Continue with the smdh file
	sprintf(buffer, "\%s\%s\%s.smdh", HBPATH, app.name, app.name);
	fp = fopen(buffer, "w+");
	fclose(fp);
	return 0;
}