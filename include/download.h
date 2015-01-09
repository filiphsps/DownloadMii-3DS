#pragma once

#include <iostream>
#include <netdb.h>
#define SERVER_HOSTNAME "www.downloadmii.com"

using namespace std;
/* Public functions */
Result networkInit();
Result downloadFile(char* url, char** buf_out, u32 *size_out);

