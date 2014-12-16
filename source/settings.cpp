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
#include "INIReader.h"

using namespace std;

//ToDo: use a ini serializer to save settings.
//The reason that two diffrent libs shoykd be used is that the parser only libs are usualy faster than the serialaztion and parser libs.
char* defaultSettings = ";DownloadMii Config File\n[DownloadMii]             ; Main configuration\nversion=\"1.0.0.0\"      ; Ex: \"1.0.0.0\"\nnightly=true    	   ; Ex: true\nautoUpdate=true	       ; Ex: true\nthemePath=\"none\" 	   ; Ex: \"/3ds/downloadmii/flatTheme.dmt\"\n"; //used when the file is not found, invalid or corrupt, empty
Settings_s settings;

void settingsInit(char* settingsPath){
	
    INIReader reader(settingsPath);

    if (reader.ParseError() < 0) {
        print("Error, cant parse ini file(might be null)\n");
		print("settingsInit: resseting/creating settings file... ");
		createSettings();
		print("Done!\n");
		print("settingsInit: re-running function...\n");
		settingsInit(settingsPath);
    }
	else{
		settings.version = (char*)reader.Get("DownloadMii", "version", "UNKNOWN").c_str();
		settings.nightly = reader.GetBoolean("DownloadMii", "nightly", true);
		settings.autoUpdate = reader.GetBoolean("DownloadMii", "autoUpdate", true);
		settings.themePath = (char*)reader.Get("DownloadMii", "themePath", "UNKNOWN").c_str();
		print("settingsInit: correctly parsed!\n");
	}
}

void createSettings(){
	mkdir("sdmc:/3ds/downloadmii", 0777);
	FILE *fh = fopen("sdmc:/3ds/downloadmii/settings.ini", "w+");
	if ( fh != NULL )
	{
		fprintf(fh, defaultSettings);
		fclose(fh);
		print("createSettings: settings.ini generated!\n");
	}
	else{
		fclose(fh);
		print("createSettings: Error, couldnt create file settings.ini\n");
	}
}
