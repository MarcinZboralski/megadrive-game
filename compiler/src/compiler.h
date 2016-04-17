#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "stdio.h"
#include "windows.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define smeMAP_SOLID_Empty          0   // empty tile
#define smeMAP_SOLID_Block          1   // blocking tile
#define smeMAP_SOLID_Special        2   // special tile, ex: sidewalks
#define smeMAP_SOLID_SwitchHuman    3   // switch plane tile, for human
#define smeMAP_SOLID_SwitchVehicle  4   // switch plane tile, for vehicle
#define smeMAP_SOLID_Water          5   // water tile
#define smeMAP_SOLID_Count          6

#endif
