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
#include "picojson.h"
#include "error.h"

using namespace std;

vector<Application_s> topApps;
vector<Application_s> topGames;
vector<Application_s> overviewApps;
vector<Application_s> staffSelectApps;
vector<Application_s> InstalledApps;
vector<Application_s> devList;

char easytolower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

Result updateAppList(vector<Application_s> *AppList, char* jsonURL){

	vector<Application_s> tempV;
	char* jsonsource;
	u32 size;
	downloadFile(jsonURL, &jsonsource, &size);
	if (jsonsource == 0) return -1; //Null check

	/* Parse json and put it into the temp vector */
	picojson::value v;
    char* json = (char*) malloc(strlen(jsonsource)+1);
    strcpy(json, jsonsource);
    string err = picojson::parse(v, json, json + strlen(json));
	print(err.c_str());
    picojson::array list = v.get("Apps").get<picojson::array>();
	
	Application_s app;
	string ap1;
	string ap2;
    for (picojson::array::iterator iter = list.begin(); iter != list.end(); iter++) {
		print(app.name.c_str());
		app.GUID =          (char*)(*iter).get("guid").get<string>().c_str();
		app.name =          (char*)(*iter).get("name").get<string>().c_str();
		app.publisher =     (char*)(*iter).get("publisher").get<string>().c_str();
		app.version =       (char*)(*iter).get("version").get<string>().c_str();
		app.description =   (char*)(*iter).get("description").get<string>().c_str();
		app.category =      (char*)(*iter).get("category").get<string>().c_str();
		app.subcategory =   (char*)(*iter).get("subcategory").get<string>().c_str();
		app.othercategory = (char*)(*iter).get("othercategory").get<string>().c_str();
		app._3dsx         = (char*)(*iter).get("3dsx").get<string>().c_str();
		app.smdh =          (char*)(*iter).get("smdh").get<string>().c_str();
		app.raiting =       (int)(*iter).get("rating").get<double>();
		
		for (auto tempApp : InstalledApps) { //Check if app is installed
			ap1 = app.name;
			transform(ap1.begin(), ap1.end(), ap1.begin(), easytolower);
			ap2 = tempApp.name;
			transform(ap2.begin(), ap2.end(), ap2.begin(), easytolower);

			app.installed = false;
			app.updateAvalible = false;
			if (ap1 == ap2) {
				app.installed = true;
				//if (app.version != tempApp.version)
				//	app.updateAvalible = true;
				break;
			}
		}
		tempV.push_back(app);
    }
	print("\n");
	*AppList = tempV;
	if(!AppList->empty()) // NULL/Empty check
		return 0;
	else{
		print("Error, failed to do updateAppList()\n");
		return -1;
	}
}

Result doListUpdate(){
	char buffer[256];
	bool hasFailed = false;
	//ToDo: replace with real url's
	//Update installed apps
	Result r = updateInstalledList(InstalledApps);
	if (r != 0) {
		print("updateInstalledList: error %s\n", getErrorMsg(r));
	}

	r = updateAppList(&overviewApps, "http://downloadmii.filfatstudios.com/testing/apps.json");
	if(r != 0){
		print("updateAppList(1): Error\n");
	}
	/*snprintf(buffer, 256, "http://%s/api/apps/TopDownloadedApps/", APIDOMAIN);
	r = updateAppList(&topApps, buffer);
	if (r != 0) {
		print("updateAppList(2): Error\n");
	}
	snprintf(buffer, 256, "http://%s/api/apps/TopDownloadedGames/", APIDOMAIN);
	r = updateAppList(&topGames, buffer);
	if (r != 0) {
		print("updateAppList(3): Error\n");
	}
	snprintf(buffer, 256, "http://%s/api/apps/StaffPicks/", APIDOMAIN);
	r = updateAppList(&staffSelectApps, buffer);
	if (r != 0) {
		print("updateAppList(4): Error\n");
	}*/
	if (hasFailed)
		return -2;
	else
		return 0;
}

Result updateDevList(vector<Application_s> *AppList, char* developer) {
	char buffer[256];
	snprintf(buffer,256, "http://%s/api/bydev/%s/", APIDOMAIN,developer);
	return updateAppList(AppList, buffer);
}

Result checkUpdate(char* currentVersion) {
	char buffer[256];
	char* remoteVersion;
	int ret = -1;
	u32 size;
	downloadFile("http://build.filfatstudios.com:8080/job/DownloadMii%20(3DS)/lastSuccessfulBuild/artifact/VERSION", &remoteVersion, &size);
	int a = strcmp(currentVersion, remoteVersion);
	if (a != 0 && remoteVersion != NULL) {
		sceneTitle = "Update Available";
		bool running = true;
		while (running == true)
		{
			UpdateInput(&Input);
			if (Input.B) {
				break;
			}
			for (auto &but : vButtons) {
				if (but.pressed) {
					//ToDo: download and install update
					Application_s dmii;
					dmii.name = "downloadmii";
					dmii.version = remoteVersion;
					dmii._3dsx = "http://build.filfatstudios.com:8080/job/DownloadMii%20(3DS)/lastSuccessfulBuild/artifact/DownloadMii.3dsx"; //ToDo: change to an release url
					dmii.smdh = "http://build.filfatstudios.com:8080/job/DownloadMii%20(3DS)/lastSuccessfulBuild/artifact/DownloadMii.smdh";  //ToDo: dito

					installApp(dmii);
					//ToDo: reload itself instead of exiting
					ret = 0;
					running = false;
					break;
				}
			}
			for (int x = 0; x <= 1; x++) {
				screen.screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
				screen.screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
				screen.screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
				renderUpdate(currentVersion, remoteVersion);
				renderDebug();
				gfxFlushBuffers();
				gfxSwapBuffers();
				gspWaitForVBlank();
			}
		}
	}
	return ret;
}