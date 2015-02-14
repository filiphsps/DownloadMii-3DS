/*------------------------------------------------------
					DownloadMii
			© Filiph Sandström 2014-2015

		TODO:
		* Clean-up

		CONTRIBUTORS:
		* Filiph Sandström (filfat)
		* ichfly
		* Joostin
------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include "main.h"
#include "utils.h"
#include "application.h"
#include "gui.h"
#include "input.h"
#include "download.h"
#include "font.h"
#include "splash.h"
#include "dataHandler.h"
#include "settings.h"
#include "music.h"
#include "md5.h"

using namespace std;

Input_s Input;
char superStr[9192];
char* jsonSS;

u64 tickOld = 0;
int fps = 0; // int instead of u32/s32 so gcc doesn't complain about different signedness.
int cfps;

int currentMenu = -1;
int currentLoop = 0;

//Todo:
Application_s currentApp;
Category_s currentCat;

#ifdef DEBUG
static int CalcFPS(); //ToDo: move to utils.cpp
#endif
char* getVersion();
char* getApiVersion();

int main(int argc, char** argv)
{
	//Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInitDefault();
	fsInit();
	sdmcInit();
	guiInit();
	settingsInit(DEFAULT_SETTINGS_PATH); //broken 
	gfxSet3D(false);
    gspWaitForVBlank(); //wait to let the app register itself

	doSplash(); //Splash Screen

	print("networkInit: started...\n");
	Result r = networkInit();
	if(r != 0){
		settings.internetConnection = false;
		print("networkInit: Error!\n");
	}
	else
	{
		settings.internetConnection = true;
		print("Network connection is active!\n");
	}

	u8 isN3DS=0;
	APT_CheckNew3DS(NULL, &isN3DS);
	if(isN3DS){
		aptOpenSession();
		r = APT_SetAppCpuTimeLimit(NULL, 80);
		if(r != 0){
			print("APT_SetAppCpuTimeLimit: Error\n");
		}
		aptCloseSession();
	}
	else {
		aptOpenSession();
		r = APT_SetAppCpuTimeLimit(NULL, 30);
		if (r != 0) {
			print("APT_SetAppCpuTimeLimit: Error\n");
		}
		aptCloseSession();
	}

	print("Getting remote api version\n");
	settings.apiVersion = "1.2.0.0"/*getApiVersion()*/; //Temporary
	print(settings.apiVersion.c_str());
	print("\n");
	print("Getting DownloadMii version...\n");
	settings.version = getVersion();

#ifdef DEBUG
	renderDebugLog();
#endif
	if (settings.internetConnection) {
		r = doListUpdate();
		if (r != 0) {
			print("doUpdate: Error\n");
		}
	}
	else {
		r = updateInstalledList(InstalledApps);
	}

	fadeOut();
	debugfnt = fontBlack;

	/* Main loop */
	int lastScene = 0;
	int lastMenu = -1;
	char buffer[256];
	if (settings.internetConnection) {
		r = checkUpdate(getVersion()); //ToDo: use settings.ini
		if (r == 0) goto EXIT;
	}
	setStoreFrontImg("http://www.downloadmii.com/banner.bin");
	print("All init done, entering main loop!\n");
	while (aptMainLoop())
	{
	loopStart:
		currentLoop++;
#ifdef DEBUG
		FPS = CalcFPS();
#endif
		if (currentLoop > 2 && !settings.acceptedBeta) {
			vButton_s but;
			but.ID = 0;
			but.x = 50;
			but.y = 151;
			but.x2 = 141;
			but.y2 = 179;
			but.menu = 0;
			addVButton(but);
		}
		UpdateInput(&Input);
		
		switch(currentMenu){
			case 0: //Overview
				if((Input.L && (scene < maxScene)) && settings.internetConnection){
					scene++;
				} else if((Input.R && (scene - 1 >= -1)) && settings.internetConnection){
					scene--;
				} else if(hidKeysHeld() & KEY_DOWN){
					if(!(VSPY + 10 > VSTY - 240))
						VSPY += 10;
					else{
						VSPY = VSTY - 240;
						//ToDo: Indicator that we have hit the end of the list
					}
				} else if(hidKeysHeld() & KEY_UP){
					if(!(VSPY - 10 <= 0))
						VSPY -= 10;
					else{
						VSPY = 0;
						//ToDo: Indicator that we have hit the start of the list
					}
				}
				//Loop through all the buttons
				if (scene != -1) {
					for (auto &but : vButtons) {
						if (but.pressed) {
							currentApp = but.app;
							currentMenu = but.menu;
						}
					}
				}
				else {
					for (auto &but : vButtons) {
						if (but.pressed) {
							currentCat.name = but.name;
							currentMenu = but.menu;
						}
					}
				}
				if(lastScene != scene){
					switch(scene){
						case -1: //Not implemented yet
							tCatList = categories;
							sceneTitle = "Categories(not implemented)";
							break;
						case 0:
							sceneTitle = "Overview";
							if (!settings.internetConnection)
								setAppList(InstalledApps); //If no internet, set applist to installed apps
							else
								setAppList(overviewApps);
							break;
						case 1:
							sceneTitle = "Top Downloaded Applications";
							if (!settings.internetConnection)
								setAppList(InstalledApps); //If no internet, set applist to installed apps
							else
								setAppList(topApps);
							break;
						case 2:
							sceneTitle = "Top Downloaded Games";
							if (!settings.internetConnection)
								setAppList(InstalledApps); //If no internet, set applist to installed apps
							else
								setAppList(topGames);
							break;
						case 3:
							sceneTitle = "Staff Pick";
							if (!settings.internetConnection)
								setAppList(InstalledApps); //If no internet, set applist to installed apps
							else
								setAppList(staffSelectApps);
							break;
						default:
							scene = 0;
					}
					lastScene = scene;
				}
				break;
			case 1: //Settings
				if(lastMenu != currentMenu)
					sceneTitle = "Settings";
				break;
			case 2: //App Page
				if(lastMenu != currentMenu){
					sceneTitle = (char*)currentApp.name.c_str();
					//setStoreFrontImg(currentApp.background);
				}
				if (Input.B) {
					currentMenu = 0;
				}
				for (auto &but : vButtons) {
					if ((but.pressed && but.ID == 0) || Input.A) { //Download
						clearVButtons();
						currentMenu = 3;
						installApp(currentApp);
						goto loopStart;
					}
					else if (but.pressed && but.ID == 1){ //Publisher
						clearVButtons();
						currentMenu = 4;
						goto loopStart;
					}
				}
				break;
			case 3: //Downloads
				if(lastMenu != currentMenu)
					sceneTitle = "Downloads";
				if (Input.B) {
					currentMenu = 0;
				}
				break;
			case 4: //by dev
				if (lastMenu != currentMenu){
					snprintf(buffer,256, "Applications By %s\n", currentApp.publisher.c_str());
					sceneTitle = (char*)buffer;
					r = updateDevList(&devList, (char*)currentApp.publisher.c_str());
					setAppList(devList);
				}
				break;
			case 5:
				if (lastMenu != currentMenu) {
					snprintf(buffer, 256, "%s\n", currentCat.name.c_str());
					sceneTitle = (char*)buffer;
					snprintf(buffer, 256, "http://%s/newApi/categories/%s", APIDOMAIN, currentCat.name.c_str());
					updateAppList(&tempCatAppList, buffer);
					setAppList(tempCatAppList);
				}
				break;
			default:
				currentMenu = 0;
				lastMenu = -1;
				break;
		}
		if (lastMenu != currentMenu) {
			clearVButtons();
			lastScene = -1;
			lastMenu = currentMenu;
			screen.topUpdated = true;
			screen.bottomUpdated = true;
		}
		gspWaitForVBlank();
		renderGUI();
		if (currentLoop > 2 && !settings.acceptedBeta) {
			guiPopup("Beta Software!", "DownloadMii is early stage software!\nBy using it you agree to terms on\nwww.downloadmii.com", "I Agree!", NULL, screen.screenBottom);
			
			for (auto &but : vButtons) {
				if (but.pressed) {
					settings.acceptedBeta = true;
					break;
				}
			}
			clearVButtons();
		}
		draw();

		/* In case of start, exit the app */
		if (Input.Start){
			print("Exiting..\n");
			//ToDo: Menu
			break;
		}
	}
	//Exit services
EXIT:
	settingsExit(DEFAULT_SETTINGS_PATH);
	fsExit();
	sdmcExit();
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}

char* getVersion() {
	char* filePath = (char*)malloc(256);
	snprintf(filePath, 256, "/%s/downloadmii/VERSION", HBPATH);
	char* fileContent;
	int size;
	Result r = loadfile(filePath, &size, &fileContent);
	if (r != 0) {
		print("Failed to get current app version, defaulting to 0.0.0.0\n");
		return "0.0.0.0";
	}
	return fileContent;
}

char* getApiVersion() {
	char* file;
	u32 size;
	Result r = downloadFile("http://www.downloadmii.com/newApi/version", &file, &size);
	if (r != 0) {
		r = downloadFile("http://www.downloadmii.com/api/version", &file, &size);
		if (r != 0) {
			return "0.0.0.0";
		}
	}
	return file;
}

#ifdef DEBUG
static int CalcFPS(){
	if (svcGetSystemTick() >= tickOld + 268123480)
	{
		tickOld = svcGetSystemTick();
		cfps = fps;
		fps = 0;
	}
	return cfps;
}
#endif