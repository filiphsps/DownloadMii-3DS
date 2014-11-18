#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include "utils.h"
#include "application.h"
#include "gui.h"

using namespace std;

Application_s defineApplication_s(int id, string name, string owner){
	Application_s App;
	App.id = id;
	App.Name = name;
	App.Owner = owner;
	return App;
}

Application_s getApp(int id){
	ostringstream convert;
	convert << "App " << id;
	Application_s test = defineApplication_s(id, convert.str(), "Test Owner");
	return test;
}