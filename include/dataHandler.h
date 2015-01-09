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

Result updateAppList(std::vector<Application_s> *AppList, char* jsonURL);
Result doListUpdate();
Result updateDevList(std::vector<Application_s> *AppList, char* developer);
Result checkUpdate(char* currentVersion);