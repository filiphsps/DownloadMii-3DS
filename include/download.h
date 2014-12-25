#pragma once

#include <iostream>
#include <netdb.h>
#include "file.h"
#define SERVER_HOSTNAME "downloadmii.filfatstudios.com"

using namespace std;
/* Public functions */
Result networkInit();
char* downloadFile(char*);
char* downloadFile(char*, u32 *size);

