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
#include "INIReader.h"

using namespace std;

char* defaultSettings = "todo"; //used when the file is not found, invalid or corrupt, empty
Settings_s settings;

void settingsInit(char* settingsPath){
	
    INIReader reader(settingsPath);

    if (reader.ParseError() < 0) {
        print("Error, cant parse ini file(might be null)\n");
		print("settingsInit: resseting/creating settings file... ");
		//ToDo
		print("Done!\n");
    }
	else{
		settings.version = (char*)reader.Get("DownloadMii", "version", "UNKNOWN").c_str();
		settings.nightly = reader.GetBoolean("DownloadMii", "nightly", true);
		settings.autoUpdate = reader.GetBoolean("DownloadMii", "autoUpdate", true);
		settings.themePath = (char*)reader.Get("DownloadMii", "themePath", "UNKNOWN").c_str();
	}
}
