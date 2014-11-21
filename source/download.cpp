#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <netdb.h>
#include "download.h"

using namespace std;

Result networkInit(){
	Result r;
	Handle h = 0;
	r = HTTPC_Initialize(h);
	if(r != 0){ //Error
		return r;
	}
	r = HTTPC_Initialize(h);
	if(r != 0){ //Error
		return r;
	}
	
	return 0; //Success
}
string downloadFile(string url){
	Result r;
	Handle h = 0;
	Handle c = 0;
	u8* b = (u8*)malloc(BUFFER_SIZE); //buffer
	r = HTTPC_CreateContext(h, const_cast<char*>(url.c_str()), &c);
	if(r != 0){ //Error
		return "error";
	}
	r = HTTPC_InitializeConnectionSession(h, c);
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
	string data;
	sprintf( const_cast<char*>(data.c_str()), "%s",b) ; //Places the content of the buffer inside "data"
	free(b);
	return data;
}