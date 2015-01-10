#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include <vector>
#include <errno.h>
#include "settings.h"
#include "gui.h"
#include "Simpleini.h"

using namespace std;

//ToDo: use a ini serializer to save settings.
//The reason that two diffrent libs should be used is that the parser only libs are usualy faster than the serialaztion and parser libs.
char* defaultSettings = ";DownloadMii Config File\n[DownloadMii]             ; Main configuration\nnightly=true    	   ; Ex: true\nautoUpdate=true	       ; Ex: true\nthemePath=\"none\" 	   ; Ex: \"/3ds/downloadmii/flatTheme.dmt\"\n"; //used when the file is not found, invalid or corrupt, empty
Settings_s settings;

Result settingsInit(char* settingsPath){
	//Load data
	string data;
	char *file_contents;
	long input_file_size;
	FILE *input_file = fopen(settingsPath, "rb");
	fseek(input_file, 0, SEEK_END);
	input_file_size = ftell(input_file);
	rewind(input_file);
	file_contents = (char*)malloc(input_file_size * (sizeof(char)));
	fread(file_contents, sizeof(char), input_file_size, input_file);
	fclose(input_file);
	data = file_contents;

	CSimpleIniA ini(true,true,true);
	SI_Error rc = ini.LoadData(data);

    if (rc < 0) {
        print("Error, cant parse ini file(might be null)\n");
		print("settingsInit: resseting/creating settings file... ");
		createSettings();
		print("Done!\n");
		print("settingsInit: re-running function...\n");
		settingsInit(settingsPath);
    }
	else{
		settings.nightly = ini.GetBoolValue("DownloadMii", "nightly", false);
		settings.autoUpdate = ini.GetBoolValue("DownloadMii", "autoUpdate", false);
		settings.themePath = ini.GetValue("DownloadMii", "themePath", "none");
		print("settingsInit: correctly parsed!\n");
	}
	return 0;
}

Result settingsExit() {
	return 0;
}

Result createSettings(){
	mkdir("sdmc:/3ds/downloadmii", 0777);
	FILE *fh = fopen("sdmc:/3ds/downloadmii/settings.ini", "w+");
	if ( fh != NULL )
	{
		fprintf(fh, defaultSettings);
		fclose(fh);
		print("createSettings: settings.ini generated!\n");
		return 0;
	}
	else{
		print("createSettings: Error, couldnt create file settings.ini\n");
	}
	return -1;
}
