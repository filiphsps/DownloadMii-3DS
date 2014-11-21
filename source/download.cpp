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
string downloadJson(char* url){
	Result r;
	Handle h = 0;
	Handle c; //contex
	r = HTTPC_CreateContext(h, url, &c);
	if(!(r == 0)){ //Error
		return "error";
	}
	r = HTTPC_InitializeConnectionSession(h, c);
	if(!(r == 0)){ //Error
		return "error";
	}
	r = HTTPC_CloseContext(h, c);
	if(!(r == 0)){ //Error
		return "error";
	}
	return "ToDo";
}