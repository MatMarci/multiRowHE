#pragma once

#include <map>
#include <vector>

using namespace std;

class ControlArea;

class ArrayOperation
{

    map<int, vector<ControlArea>> areas;
    map<int, vector<ControlArea>> *areasPointer;

public:
    map<int, vector<ControlArea>>* initalizeModel(bool isFlowAlternately);
    void setAirAndWaterFlow(bool isFlowAlternately);
    void setInitialValues(map<int, vector<ControlArea>> &areas, bool isFlowAlternately);
};
