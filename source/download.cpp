#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <netdb.h>
#include "download.h"
#include "settings.h"
#include "gui.h"


using namespace std;
httpcContext context;
u32 statuscode = 0;
int runCount;

Result networkInit(){
	httpcInit();
	Result result = httpcOpenContext(&context, "http://www.downloadmii.com", 0); //Test internet connection
	if (result != 0) {
		httpcCloseContext(&context);
		return -3;
	}
	result = httpcBeginRequest(&context);
	if (result != 0) {
		httpcCloseContext(&context);
		return -1;
	}
	httpcCloseContext(&context);
	return 0;
}

Result downloadFile(char* url, char** buffer, u32 *size) {
	Result result;

	result = httpcOpenContext(&context, url, 0);
	if (result != 0) {
		print("httpcOpenContext returned 0x%08X\n", (int)result);
		httpcCloseContext(&context);
		print("error: httpcOpenContext\n");
		return -3;
	}

	result = httpcBeginRequest(&context);
	if (result != 0) {
		httpcCloseContext(&context);
		print("error: httpcBeginRequest\n");

		runCount++;
		if (runCount <= 10) {
			downloadFile(url, buffer, size); //ReRun function
		}
		else {
			print("Error, download function stuck in loop! recovering...\n");
			runCount = 0;
		}
		return -1;
	}
	else
	{
		runCount = 0;
	}

	result = httpcGetResponseStatusCode(&context, &statuscode, 0);
	if ((result != 0) || statuscode != 200 || statuscode == 403) {
		httpcCloseContext(&context);
		print("error: httpcGetResponseStatusCode\n");
		return -7;
	}
	else if (statuscode == 999) { //Service closed
		httpcCloseContext(&context);
		return -200;
	}
	result = httpcGetDownloadSizeState(&context, NULL, size);
	if (result != 0) {
		httpcCloseContext(&context);
		print("error: httpcGetDownloadSizeState\n");
		return -1;
	}

	*buffer = (char*)calloc(*size, 1);
	if (*buffer == NULL) {
		httpcCloseContext(&context);
		print("error: (char*)\n");
		return -1;
	}

	u32 size2;
	result = httpcDownloadData(&context,(u8*)*buffer, *size, &size2);
	if (result != 0)
	{
		free(*buffer);
		httpcCloseContext(&context);
		print("error: httpcDownloadData\n");
		return -1;
	}
	print("Download size: %d\n", (int)*size);
	httpcCloseContext(&context);
	return 0;
}
