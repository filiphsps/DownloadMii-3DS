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
	char* filesmdh;
	r = downloadFile((char*)app.smdh.c_str(), &filesmdh, &size[1]);
	temp = filesmdh;
	replace(temp, "https", "http");
	r = downloadFile((char*)temp.c_str(), &filesmdh, &size[1]);
	if (r != 0) {
		return -1;
	}
	print("smdh downloaded\n");


	/* Save files to the SD-Card */

	//Start with the elf file
	snprintf(buffer,256, "/%s/%s/%s.3dsx", HBPATH, app.name.c_str(), app.name.c_str());
	fp = fopen(buffer, "w+");
	fwrite(file3dsx, sizeof(file3dsx[0]), size[0], fp);
	fclose(fp);
	print("3dsx saved\n");

	//Continue with the smdh file
	snprintf(buffer,256, "/%s/%s/%s.smdh", HBPATH, app.name.c_str(), app.name.c_str());
	fp = fopen(buffer, "w+");
	fwrite(filesmdh, sizeof(filesmdh[0]), size[1], fp);
	fclose(fp);
	print("smdh saved\n");

	//End with the VERSION file
	snprintf(buffer, 256, "/%s/%s/VERSION", HBPATH, app.name.c_str());
	fp = fopen(buffer, "w+");
	snprintf(buffer,256, "%s", app.version.c_str());
	fprintf(fp,buffer);
	fclose(fp);
	print("VERSION saved\n");
	if (app.appdata != "" && app.appdata != "null") { //if the app has extra data, download and unzip it.
		print("Downloading and unzipping appdata... ");
		r = dlAndUnZip((char*)app.appdata.c_str(), "unused", (char*)app.name.c_str());
		if (r != 0) {
			print("Error: %s\n", getErrorMsg(r));
		}
		print("Done!\n");
	}
	else {
		print("No appdata found\n");
	}
	print("Done Installing app, updating list...\n");
	r = doListUpdate();
	free(file3dsx);
	free(filesmdh);
	return 0;
}

Result installTheme(Theme_s app) {
	if (!settings.internetConnection)
		return -1;
	return -99;
}

bool unzipArchive(char * zipfilepath, char * unzipfolderpath)
{
	const char *FileToExtract = zipfilepath;
	const char *DirTe = unzipfolderpath;
	const char *Password = NULL;
	sdmcArchive = (FS_archive) { 0x9, (FS_path) { PATH_EMPTY, 1, (u8*)"" } };
	FSUSER_OpenArchive(NULL, &sdmcArchive);
	FS_path TEMP_PATH = FS_makePath(PATH_CHAR, DirTe);
	FSUSER_CreateDirectory(NULL, sdmcArchive, TEMP_PATH);
	FSUSER_CloseArchive(NULL, &sdmcArchive);
	char tmpFile2[1024];
	char tmpPath2[1024];
	sdmcInit();
	strcpy(tmpPath2, "sdmc:");
	strcat(tmpPath2, (char*)DirTe);
	chdir(tmpPath2);
	strcpy(tmpFile2, "sdmc:");
	strcat(tmpFile2, (char*)FileToExtract);
	Zip *handle = ZipOpen(tmpFile2);
	if (handle == NULL) print("error opening ZIP file.\n");
	int result = ZipExtract(handle, Password);
	ZipClose(handle);
	sdmcExit();
	return 1;
}

Result dlAndUnZip(char* url, char* path, char* appname) {
	char buffer[256];
	char buffer2[256];
	FILE *fp;
	/* Download File */
	char* file;
	u32 size;
	Result r = downloadFile(url, &file, &size);
	string temp = file;
	replace(temp, "https", "http");
	file = (char*)temp.c_str();
	r = downloadFile(file, &file, &size);
	/* Save Zip File */
	snprintf(buffer, 255, "/%s/%s/%s.zip", HBPATH, appname, "appdata");
	snprintf(buffer2, 255, "/%s/%s/", HBPATH, appname);
	fp = fopen(buffer, "w+");
	fwrite(file, sizeof(file), size, fp);
	fclose(fp);
	unzipArchive(buffer, buffer2);

	return 0;
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
					//print("%s\n", tempPath);
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