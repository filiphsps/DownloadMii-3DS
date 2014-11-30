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
	Result result;
	httpcContext context;
	u8 *buffer;
	u32 statuscode=0;
	u32 contentsize=0;
	char* file;
	
	result = httpcOpenContext(&context, url, 0);
	if(result != 0){
		print("error: httpcOpenContext");
		return "error: httpcOpenContext";
	}
	
	result = httpcBeginRequest(&context);
	if(result != 0){
		print("error: httpcBeginRequest");
		return "error: httpcBeginRequest";
	}
	
	result = httpcGetResponseStatusCode(&context, &statuscode, 0);
	if((result != 0) || statuscode != 200){
		print("error: httpcGetResponseStatusCode");
		return "error: httpcGetResponseStatusCode";
	}
	
	result = httpcGetDownloadSizeState(&context, NULL, &contentsize);
	if(result != 0){
		print("error: httpcGetDownloadSizeState");
		return "error: httpcGetDownloadSizeState";
	}
	
	buffer = (u8*)calloc(contentsize, sizeof(u8*));
	if(buffer==NULL)return "error: (u8*)malloc(contentsize)";
	
	result = httpcDownloadData(&context, buffer, contentsize, NULL);
	if(result != 0)
	{
		free(buffer);
		print("error: httpcDownloadData");
		return "error: httpcDownloadData";
	}
	file = (char*)buffer;
	free(buffer);
	httpcCloseContext(&context);
	return file;
}
