#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include <zlib.h>
#include "main.h"
#include "application.h"
#include "download.h"
#include "gui.h"
#include "utils.h"
#include "settings.h"
#include "md5.h"
#include "dataHandler.h"
#include "error.h"

using namespace std;

FS_archive sdmcArchive;

void ProgressBarRender(u32 dummy) {
	while (progressbar.used) {
		renderAppPage();
		gspWaitForVBlank();
	}
}

Result installApp(Application_s app){
	if (!settings.internetConnection)
		return -1;
	//ToDo
	print("Installing App..\n");
	progressbar.progress = 0;
	progressbar.used = true;
	/*Handle threadHandle;
	u32 *stack = (u32*)malloc(0x4000);
	svcCreateThread(&threadHandle, ProgressBarRender, 0, &stack[0x4000 >> 2], 0, 3);*/
	Result r;
	char buffer[1024];
	u32 size[2];
	FILE *fp;
	string temp;
	/* MKDIR */
	snprintf(buffer,256, "/%s/%s", HBPATH, app.name.c_str());
	mkdir(buffer, 0777);

	progressbar.progress = 10;

	/* Download Files */
	char* file3dsx;
	r = downloadFile((char*)app._3dsx.c_str(), &file3dsx, &size[0]);
	temp = file3dsx;
	replace(temp, "https", "http");
	r = downloadFile((char*)temp.c_str(), &file3dsx, &size[0]);
	if (r != 0) {
		return -1;
	}
	print("3dsx downloaded\n");
	progressbar.progress = 30;
	char* filesmdh;
	r = downloadFile((char*)app.smdh.c_str(), &filesmdh, &size[1]);
	temp = filesmdh;
	replace(temp, "https", "http");
	r = downloadFile((char*)temp.c_str(), &filesmdh, &size[1]);
	if (r != 0) {
		return -1;
	}
	print("smdh downloaded\n");
	progressbar.progress = 50;
	/* Save files to the SD-Card */
	//Start with the elf file
	snprintf(buffer,256, "/%s/%s/%s.3dsx", HBPATH, app.name.c_str(), app.name.c_str());
	fp = fopen(buffer, "w+");
	fwrite(file3dsx, sizeof(file3dsx[0]), size[0], fp);
	fclose(fp);
	print("3dsx saved\n");
	progressbar.progress = 65;
	//Continue with the smdh file
	snprintf(buffer,256, "/%s/%s/%s.smdh", HBPATH, app.name.c_str(), app.name.c_str());
	fp = fopen(buffer, "w+");
	fwrite(filesmdh, sizeof(filesmdh[0]), size[1], fp);
	fclose(fp);
	print("smdh saved\n");
	progressbar.progress = 80;
	//End with the VERSION file
	snprintf(buffer, 256, "/%s/%s/VERSION", HBPATH, app.name.c_str());
	fp = fopen(buffer, "w+");
	snprintf(buffer,256, "%s", app.version.c_str());
	fprintf(fp,buffer);
	fclose(fp);
	print("VERSION saved\n");
	progressbar.progress = 85;
	if (app.dataZip != "" && app.dataZip != "NULL") { //if the app has extra data, download and unzip it.
		print("unZipping data... ");
		snprintf(buffer, 256, "/%s/%s/", HBPATH, app.name.c_str());
		//r = dlAndUnZip((char*)app.dataZip.c_str(), buffer, (char*)app.name.c_str());
		if (r != 0) {
			print("Error: %s\n", getErrorMsg(r));
		}
		print("Done!\n");
	}
	print("Done Installing app, updating list...\n");
	progressbar.progress = 95;
	r = doListUpdate();
	free(file3dsx);
	free(filesmdh);
	progressbar.progress = 100;
	progressbar.used = false;
	return 0;
}

Result dlAndUnZip(char* url, char* path, char* appname) {
	char buffer[1024];
	FILE *fp;
	/* Download File */
	char* file;
	u32 size;
	Result r = downloadFile(url, &file, &size);
	r = downloadFile(file, &file, &size);
	/* Save Zip File */
	snprintf(buffer, 256, "sdmc:/%s/%s/%s.zip", HBPATH, appname, "appdata");
	fp = fopen(buffer, "w+");
	fwrite(file, sizeof(file), size, fp);
	fclose(fp);
	//ToDo: unzip zip file
	fp = fopen(buffer, "rb");
	fclose(fp);

	return -99;
}

Result updateInstalledList(vector<Application_s> &list) {
	list.clear();
	Application_s tempApp;
	//Stolen from HBMenu(modified)
	sdmcArchive = (FS_archive) { 0x00000009, (FS_path) { PATH_EMPTY, 1, (u8*)"" } };
	FSUSER_OpenArchive(NULL, &sdmcArchive);
	Handle dirHandle;
	FS_path dirPath = FS_makePath(PATH_CHAR, "/3ds/");
	FSUSER_OpenDirectory(NULL, &dirHandle, sdmcArchive, dirPath);

	static char fullPath[1024];
	static char tempPath[1024];
	u32 entriesRead;
	do
	{
		FS_dirent entry;
		memset(&entry, 0, sizeof(FS_dirent));
		entriesRead = 0;
		FSDIR_Read(dirHandle, &entriesRead, 1, &entry);
		if (entriesRead)
		{
			strncpy(fullPath, "/3ds/", 1024);
			int n = strlen(fullPath);
			unicodeToChar(&fullPath[n], entry.name, 1024 - n);
			if (entry.isDirectory) //directories
			{
				snprintf(tempPath,1024, "%s", fullPath);
				if (tempPath[5] != '.') {
					print("%s\n", tempPath);
					char* tp = tempPath;
					tp += 5;
					tempApp.name = tp;
					if (!settings.internetConnection) {
						tempApp.publisher = "Unknown"; //ToDo: read from smdh file if settings.internetConnection is false
						if (tempApp.name == "downloadmii") {
							tempApp.name = "DownloadMii";
							tempApp.publisher = "filfat";
						}
						tempApp.category = "Unknown";
						tempApp.installed = true;
						tempApp.updateAvalible = false;
						tempApp.raiting = 0;
					}
					char* verBuf;
					int size = 0;
					char* file = (char*)malloc(256);
					snprintf(file, 256, "/%s/%s/VERSION", HBPATH, tempApp.name.c_str());
					loadfile(file, &size, &verBuf);
					if (verBuf != NULL)
						tempApp.version = verBuf;
					else {
						tempApp.version = "0.0.0.0";
						if(tempApp.name != "downloadmii")
							tempApp.error = true;
					}
					list.push_back(tempApp);
				}
			}
		}
	} while (entriesRead);

	FSDIR_Close(dirHandle);
	FSUSER_CloseArchive(NULL, &sdmcArchive);
	return 0; //ToDo: use error codes
}