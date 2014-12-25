#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <netdb.h>
#include "download.h"
#include "gui.h"
#include "file.h"

using namespace std;

Result networkInit(){
	httpcInit();
	return 0;
}
char* downloadFile(char* url){
	print("Downloading..\n");
	Result result;
	httpcContext context;
	u8 *buffer;
	u32 statuscode=0;
	u32 contentsize=0;
	char* file;
	
	result = httpcOpenContext(&context, url, 0);
	if(result != 0){
		httpcCloseContext(&context);
		print("error: httpcOpenContext\n");
		return "error: httpcOpenContext";
	}
	
	result = httpcBeginRequest(&context);
	if(result != 0){
		httpcCloseContext(&context);
		print("error: httpcBeginRequest\n");
		return "error: httpcBeginRequest";
	}
	
	result = httpcGetResponseStatusCode(&context, &statuscode, 0);
	if((result != 0) || statuscode != 200){
		httpcCloseContext(&context);
		print("error: httpcGetResponseStatusCode\n");
		return "error: httpcGetResponseStatusCode";
	}
	
	result = httpcGetDownloadSizeState(&context, NULL, &contentsize);
	if(result != 0){
		httpcCloseContext(&context);
		print("error: httpcGetDownloadSizeState\n");
		return "error: httpcGetDownloadSizeState";
	}
	
	buffer = (u8*)calloc(contentsize, 1);
	if(buffer==NULL){
		free(buffer);
		httpcCloseContext(&context);
		print("error: (u8*)calloc(contentsize, sizeof(u8*)\n");
		return "error: (u8*)calloc(contentsize, sizeof(u8*)";
	}
	
	result = httpcDownloadData(&context, buffer, contentsize, NULL);
	if(result != 0)
	{
		free(buffer);
		httpcCloseContext(&context);
		print("error: httpcDownloadData\n");
		return "error: httpcDownloadData";
	}
	file = (char*)buffer;
	//free(buffer);
	httpcCloseContext(&context);
	return file;
}

Result downloadFile(char* url, char** buffer, u32 *size) {
	print("Downloading File...\n");
	Result result;
	httpcContext context;
	u32 statuscode = 0;

	result = httpcOpenContext(&context, url, 0);
	if (result != 0) {
		httpcCloseContext(&context);
		print("error: httpcOpenContext\n");
		return -1;
	}

	result = httpcBeginRequest(&context);
	if (result != 0) {
		httpcCloseContext(&context);
		print("error: httpcBeginRequest\n");
		return -1;
	}

	result = httpcGetResponseStatusCode(&context, &statuscode, 0);
	if ((result != 0) || statuscode != 200) {
		httpcCloseContext(&context);
		print("error: httpcGetResponseStatusCode\n");
		return -1;
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

	result = httpcDownloadData(&context,(u8*)*buffer, *size, NULL);
	if (result != 0)
	{
		free(buffer);
		httpcCloseContext(&context);
		print("error: httpcDownloadData\n");
		return -1;
	}
	httpcCloseContext(&context);
	return 0;
}