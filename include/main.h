#pragma once

#include "Input.h"

#define APPLICATION_NAME "DownloadMii"
#define APIDOMAIN "www.downloadmii.com"
#define SECONDS_IN_DAY 86400 
#define SECONDS_IN_HOUR 3600 
#define SECONDS_IN_MINUTE 60 
#define HBPATH "3ds"
#define DEBUG
#define DEFAULT_SETTINGS_PATH "sdmc:/3ds/downloadmii/settings.ini"
#define _VERSION_ "1.0.0.0"

extern int currentMenu;
extern Input_s Input;