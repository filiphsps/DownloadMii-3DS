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
	string _3dsx, md5_3dsx;
	string smdh, md5_smdh;
	int raiting;
	int downloads;

	bool installed = false, updateAvalible = false, error = false;
};

extern vector<Application_s> InstalledApps;

Result installApp(Application_s app);
Result updateInstalledList(vector<Application_s> &list);