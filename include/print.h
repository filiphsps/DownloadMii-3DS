#pragma once
#include <3ds.h>
#define print(...) snprintf(&superStr[strlen(superStr)], 9192, __VA_ARGS__); svcOutputDebugString(superStr, 9192);
extern char superStr[];