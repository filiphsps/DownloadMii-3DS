#pragma once

#include <iostream>
#include <3ds.h>
#include "file.h"

using namespace std;

struct Application_s{
	char* GUID;
	char* name;
	char* publisher;
	char* version;
	char* description;
	char* category;
	char* subcategory;
	char* othercategory;
	char* _3dsx;
	char* smdh;
	
	bool installed;
	
	//TODO: add all the values that can be found in the json file
};

//Template define: {"NULL", "DownloadMii", "filfat Studio's", "1.0.0.0", "Download Homebrew apps on your 3ds", "Utils", "Stores", "NULL", "http://downloadmii.filfatstudios.com/stable/dmii.3dsx", "http://downloadmii.filfatstudios.com/stable/dmii.smdh", 5}

Result installApp(Application_s app);