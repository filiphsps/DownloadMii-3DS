#include <iostream>
#include <vector>
#include "application.h"

#define offlineJson "{\"Apps\":{\"Tools\":[{\"name\":\"Temp\",\"owner\":\"Temp\",\"description\":\"Line 1\nLine 2\",\"subGen\":\"Theme\",\"downloadUrl\":\"http://exampke.com/temp.3dsx\",\"icon\":\"http://example.com/temp.png\",\"smdh\":\"http://example.com/temp.smdh\"},{\"name\":\"Temp2\",\"owner\":\"Temp\",\"description\":\"Line 1\nLine 2\",\"subGen\":\"Theme\",\"downloadUrl\":\"http://exampke.com/temp.3dsx\",\"icon\":\"http://example.com/temp.png\",\"smdh\":\"http://example.com/temp.smdh\"}],\"Games\":[{\"name\":\"Pong\",\"owner\":\"Temp\",\"description\":\"Line 1\nLine 2\",\"subGen\":\"Retro\",\"downloadUrl\":\"http://exampke.com/pong.3dsx\",\"icon\":\"http://example.com/pong.png\",\"smdh\":\"http://example.com/pong.smdh\"}]}}"
#define TOPAPPSJSON "http://downloadmii.filfatstudios.com/getJson.php?type=topApps"
#define APPLICATIONSJSON "http://downloadmii.filfatstudios.com/Applications.json"

using namespace std;

void jsonList2Vector(char* json, vector<Application_s> *vector_l);