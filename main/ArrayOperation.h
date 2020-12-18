#pragma once

#include <map>
#include <vector>

//#include "ControlArea.h"

using namespace std;

class ControlArea;

class ArrayOperation
{

    map<int, vector<ControlArea>> areas;

public:
    map<int, vector<ControlArea>> initalizeModel(bool isFlowAlternately);
    void setAirAndWaterFlow(bool isFlowAlternately);
};
