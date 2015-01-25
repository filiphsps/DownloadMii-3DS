#pragma once

#include <3ds.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <3ds.h>

struct Settings_s{
	bool nightly;    	//Ex: true, Unused.
	bool autoUpdate;	//Ex: true, Unused.
	bool acceptedBeta;  //Ex: true, Used.
	std::string themePath; 	//Ex: "/3ds/downloadmii/flatTheme.dmt", Unused.

	//Settings that doesnt get saved to the file:
	bool internetConnection;
	std::string version;
	std::string fileContent;
	std::string apiVersion; //The backend api version
};

extern Settings_s settings;
extern char* defaultSettings;

Result settingsInit(char* settingsPath);
Result deleteSettings();
Result createSettings();
Result settingsExit(char* settingsPath);