#pragma once

#include <iostream>
#include <3ds.h>
#include <vector>

struct Application_s{
	std::string GUID;
	std::string name;
	std::string publisher;
	std::string version;
	std::string description;
	std::string category;
	std::string subcategory;
	std::string _3dsx, md5_3dsx;
	std::string smdh, md5_smdh;
	std::string dataZip, md5_dataZip;
	int raiting;
	int downloads;

	bool installed = false, updateAvalible = false, error = false;
};

struct Category_s {
	int ID;
	std::string name;
	bool subCategories;
};

extern std::vector<Application_s> InstalledApps;

Result installApp(Application_s app);
Result updateInstalledList(std::vector<Application_s> &list);
Result dlAndUnZip(char* url, char* path, char* appname);