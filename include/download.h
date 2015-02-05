/*------------------------------------------------------
					DownloadMii
			© Filiph Sandström 2014-2015

		TODO:
		* Speed-up
		* Clean-up
		* Fix error codes

		CONTRIBUTORS:
		* Filiph Sandström (filfat)
		* Joostin
------------------------------------------------------*/
#pragma once

#include <iostream>
#include <netdb.h>
#define SERVER_HOSTNAME "www.downloadmii.com"

using namespace std;
/* Public functions */
Result networkInit();
Result downloadFile(char* url, char** buf_out, u32 *size_out);

