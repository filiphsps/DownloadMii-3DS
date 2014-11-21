#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <netdb.h>
#include "download.h"

using namespace std;

Handle h = 0;

Result networkInit(){
	srvGetServiceHandle(&h, "http:C");
	Result r;
	r = HTTPC_Initialize(h);
	if(r != 0){ //Error
		return r;
	}
	
	return 0; //Success
}
char* downloadFile(char* url){
	Result r;
	Handle c = 0;
	u8* b = (u8*)malloc(BUFFER_SIZE); //buffer
	r = HTTPC_CreateContext(h, url, &c);
	if(r != 0){ //Error
		return "error";
	}
	r = HTTPC_InitializeConnectionSession(h, c);
	if(r != 0){ //Error
		return "error";
	}
	r = HTTPC_SetProxyDefault(h, c);
	if(r != 0){ //Error
		return "error";
	}
	r = HTTPC_BeginRequest(h, c);
	if(r != 0){ //Error
		return "error";
	}
	r = HTTPC_ReceiveData(h, c, b, BUFFER_SIZE);
	if(r != 0){ //Error
		return "error";
	}
	r = HTTPC_CloseContext(h, c);
	if(r != 0){ //Error
		return "error";
	}
	return (char*)b;
}
