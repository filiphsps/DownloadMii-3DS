#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include "utils.h"
#include "application.h"
#include "download.h"

using namespace std;

Handle sdHandle;

Result installApp(Application_s app){
	//ToDo
	char buffer[110];
	/* Download Files */
	char* file3dsx = downloadFile(app.execURL);
	char* filesmdh = downloadFile(app.smdhURL);
	if(file3dsx[0] == 'e' || filesmdh[0] == 'e') //Can return false positives(rare), needs to be fixed.
		return -1; //Error
	/* Save files to the SD-Card */
	FS_archive sdmcArchive=(FS_archive){ARCH_SDMC, (FS_path){PATH_EMPTY, 1, (u8*)""}};
	sprintf(buffer, "\3ds\%s\%s.3dsx", app.name, app.name);
	FS_path filePath=FS_makePath(PATH_CHAR, buffer);
	
	sprintf(buffer, "\3ds\%s\%s.smdh", app.name, app.name);
	filePath=FS_makePath(PATH_CHAR, buffer);
	
	return 0;
}