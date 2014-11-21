#include <iostream>
#include <string.h>
#include <3ds.h>
#include <netdb.h>
#include "download.h"

using namespace std;

Result initDownload(){
	Result r;
	Handle h = 0;
	r = HTTPC_Initialize(h);
	if(!(r == 0)){ //Error
		return r;
	}
	r = HTTPC_Initialize(h);
	if(!(r == 0)){ //Error
		return r;
	}
	
	return 0; //Success
}
string downloadFile(char* url){
	Result r;
	Handle h = 0;
	Handle c; //contex
	u8 b = 0; //buffer
	u32 s = 10000; //Size
	r = HTTPC_CreateContext(h, url, &c);
	if(!(r == 0)){ //Error
		return "error";
	}
	r = HTTPC_InitializeConnectionSession(h, c);
	if(!(r == 0)){ //Error
		return "error";
	}
	r = HTTPC_BeginRequest(h, c);
	if(!(r == 0)){ //Error
		return "error";
	}
	r = HTTPC_ReceiveData(h, c, &b, s);
	if(!(r == 0)){ //Error
		return "error";
	}
	r = HTTPC_CloseContext(h, c);
	if(!(r == 0)){ //Error
		return "error";
	}
	return "ToDo";
}