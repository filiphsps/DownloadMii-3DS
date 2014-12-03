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

vector<Application_s> topApps;
vector<Application_s> topGames;
vector<Application_s> overviewApps;
vector<Application_s> staffSelectApps;

Result updateAppList(vector<Application_s> *AppList, char* jsonURL){
	print("updateAppList() is not yet implamentet\n");
	vector<Application_s> tempV;
	char* json = downloadFile(jsonURL);
	/* Parse json and put it into the temp vector */
	
	//-----<For Testing>
	Application_s app = {0, 4, "Test3DS", "filfat", "Utils", "http://downloadmii.filfatstudios.com/Applications.json", "http://downloadmii.filfatstudios.com/Applications.json"};
	tempV.push_back(app);
	tempV.push_back(app);
	tempV.push_back(app);
	//-----
	
	*AppList = tempV;
	if(!AppList->empty()) // NULL/Empty check
		return 0;
	else{
		print("Error, failed to do updateAppList()\n");
		return -1;
	}
}
