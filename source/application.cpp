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
	print("Installing App..\n");
	Result r;
	char buffer[1024];
	u32 size[1];
	FILE *fp;
	/* MKDIR */
	sprintf(buffer, "/%s/%s", HBPATH, app.name.c_str());
	mkdir(buffer, 0777);
	/* Download Files */
	char* file3dsx;
	r = downloadFile((char*)app._3dsx.c_str(), &file3dsx, &size[0]);
	print(file3dsx);
	if (r != 0) {
		return -1;
	}
	print("\n");
	char* filesmdh;
	r = downloadFile((char*)app.smdh.c_str(), &filesmdh, &size[1]);
	if (r != 0) {
		return -1;
	}
	/* Save files to the SD-Card */
	//Start with the elf file
	snprintf(buffer,256, "/%s/%s/%s.3dsx", HBPATH, app.name.c_str(), app.name.c_str());
	fp = fopen(buffer, "w+");
	fwrite(file3dsx, sizeof(file3dsx[0]), size[0], fp);
	fclose(fp);
	//Continue with the smdh file
	snprintf(buffer,256, "/%s/%s/%s.smdh", HBPATH, app.name.c_str(), app.name.c_str());
	fp = fopen(buffer, "w+");
	fwrite(filesmdh, sizeof(filesmdh[0]), size[1], fp);
	fclose(fp);
	print("Done Installing app...\n");
	return 0;
}