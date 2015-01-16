#pragma once

#include <iostream>
#include <3ds.h>
#include <vector>

#include "application.h"

extern std::vector<Application_s> topApps;
extern std::vector<Application_s> topGames;
extern std::vector<Application_s> overviewApps;
extern std::vector<Application_s> staffSelectApps;
extern std::vector<Application_s> devList;
extern std::vector<Category_s> categories;

Result updateAppList(std::vector<Application_s> *AppList, char* jsonURL);
Result updateCategories(std::vector<Category_s> *CatList, char* jsonURL);
Result doListUpdate();
Result updateDevList(std::vector<Application_s> *AppList, char* developer);
Result checkUpdate(char* currentVersion);