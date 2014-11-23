#pragma once

#include <iostream>
#include <netdb.h>
#define SERVER_HOSTNAME "downloadmii.filfatstudios.com"

using namespace std;
/* Public functions */
Result networkInit();
char* downloadFile(char*);

/* Private-ish functuons, shouldnt be used by any other class! */

