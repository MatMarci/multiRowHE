#pragma once

#include <list>

//#include "ControlArea.h"

using namespace std;

class ControlArea;

class ArrayOperation
{

    list<ControlArea> areas;

public:
    list<ControlArea> initalizeModel(bool isFlowAlternately);
};
