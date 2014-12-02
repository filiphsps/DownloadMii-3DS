#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <3ds.h>
#include "dataHandler.h"
#include "main.h"
#include "application.h"
#include "download.h"
#include "gui.h"
#include "file.h"

using namespace std;

Result updateAppList(vector<Application_s> *AppList, char* json){
	vector<Application_s> tempV;
	/* Parse json and put it into the temp vector */
	
	//TODO---------------------------------------------------------------------------
	
	*AppList = tempV;
	if(!AppList->empty()) //NULL/Empty check
		return 0;
	else{
		print("Error, failed to do updateAppList()");
		return -1;
	}
}
