#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <iostream>

using namespace std;

struct Application_s{
	int id;
	string Name;
	string Owner;
	//TODO: add all the values that can be found in the json file
	
};

Application_s defineApplication_s(int id, string name, string owner);
Application_s getApp(int id);

#endif