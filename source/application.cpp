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

Result installApp(Application_s app, char* path){
	//ToDo
	
	/* Download Files */
	char* file3dsx = downloadFile(app.execURL);
	char* filesmdh = downloadFile(app.smdhURL);
	/* Save files to the SD-Card */
	FS_archive sdmcArchive=(FS_archive){ARCH_SDMC, (FS_path){PATH_EMPTY, 1, (u8*)""}};
	FS_path filePath=FS_makePath(PATH_CHAR, path);
	
	return 0;
}