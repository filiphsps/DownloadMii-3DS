#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include <vector>
#include <errno.h>
#include "settings.h"
#include "gui.h"
#include "ini.h"

using namespace std;

Settings_s settings;
FS_archive sdmcArchive;

void settingsInit(char* settingsPath){
	char *buffer;
	FILE *fh = fopen("sdmc:/3ds/downloadmii/settings.ini", "r");
	if ( fh != NULL )
	{
		fseek(fh, 0L, SEEK_END);
		long s = ftell(fh);
		rewind(fh);
		buffer = (char*)malloc(s);
		if ( buffer != NULL )
		{
		  fread(buffer, s, 1, fh);
		  // we can now close the file
		  fclose(fh); fh = NULL;
	 
		  // do something, e.g.
		  fwrite(buffer, s, 1, stdout);
	 
		  free(buffer);
		}
		if (fh != NULL){
			fclose(fh);
			print("settingsInit: File is null(2)\n");
		}
	}
	else{
		print("settingsInit: File is null(1)\n");
	}
	
	INI::Parser p(buffer);  
	print(p.top()("DownloadMii")["version"].c_str()); 
	//settings.version = (char*)reader.Get("DownloadMii", "version", "UNKNOWN").c_str();
	//settings.nightly = reader.GetBoolean("DownloadMii", "nightly", true);
	//settings.autoUpdate = reader.GetBoolean("DownloadMii", "autoUpdate", true);
	//settings.themePath = (char*)reader.Get("DownloadMii", "themePath", "UNKNOWN").c_str();
	print(settings.version);
}
