#pragma once

#include <iostream>
#include <3ds.h>
#include <vector>
#include "file.h"
#include "application.h"

using namespace std;

Result updateAppList(vector<Application_s> *AppList, char* json);