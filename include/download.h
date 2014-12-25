#pragma once

#include <iostream>
#include <netdb.h>
#include "file.h"
#define SERVER_HOSTNAME "downloadmii.filfatstudios.com"

using namespace std;
/* Public functions */
Result networkInit();
Result downloadFile(char* url, char** buf_out, u32 *size_out);

