#pragma once

#include <iostream>
#include <3ds.h>
#include <vector>
#include "file.h"

using namespace std;

//ToDo
char* getErrorMsg(Result error) {
	switch (error) {
	case 0:
		return "No error";
	case -99:
		return "Not yet implamentet";
	default:
		return "Unknown error";
	}
}