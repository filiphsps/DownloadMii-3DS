#pragma once

#include <iostream>
#include <3ds.h>

using namespace std;

struct Application_s{
	int ID;
	int rating;
	char* name;
	char* owner;
	char* category;
	
	char* execURL;
	char* smdhURL;
	char* iconURL;
	char* websiteURL;
	
	bool installed;
	
	//TODO: add all the values that can be found in the json file
};

Result installApp(Application_s app);