#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <iostream>
#include <netdb.h>
#define SERVER_HOSTNAME "downloadmii.filfatstudios.com"

using namespace std;
/* Public functions */
Result initDownload();
string downloadJson(char* url);

/* Private-ish functuons, shouldnt be used by any other class! */

#endif
