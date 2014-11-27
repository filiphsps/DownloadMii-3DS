#pragma once

#include <iostream>

using namespace std;

struct Application_s{
	int ID;
	int rating;
	string name;
	string owner;
	string category;
	
	string execURL;
	string smdhURL;
	string iconURL;
	string websiteURL;
	
	//TODO: add all the values that can be found in the json file
};