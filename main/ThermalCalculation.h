#pragma once

#include "ControlArea.h"


class ThermalCalculation
{


public:
    void airAndWaterOutTempCalc(map<int, vector<ControlArea>> areas, bool isFlowAlternately, int iteration);
};
