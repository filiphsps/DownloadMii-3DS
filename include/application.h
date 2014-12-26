#pragma once

#include <iostream>
#include <3ds.h>
#include <vector>
#include "file.h"

using namespace std;

struct Application_s{
	string GUID;
	string name;
	string publisher;
	string version;
	string description;
	string category;
	string subcategory;
	string othercategory;
	string _3dsx;
	string smdh;
	int raiting;
	
	bool installed;
	
	//TODO: add all the values that can be found in the json file
};
//Template define: {"NULL", "DownloadMii", "filfat Studio's", "1.0.0.0", "Download Homebrew apps on your 3ds", "Utils", "Stores", "NULL", "http://downloadmii.filfatstudios.com/stable/dmii.3dsx", "http://downloadmii.filfatstudios.com/stable/dmii.smdh", 5}

extern vector<Application_s> InstalledApps;

Result installApp(Application_s app);
Result updateInstalledList(vector<Application_s> *list);