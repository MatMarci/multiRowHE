#pragma once

#include "ControlArea.h"


class ThermalCalculation
{


public:
    void airOutTempCalc(vector<ControlArea> &areas, bool isFlowAlternately);
    void waterOutTempCalc(vector<ControlArea> &areas, bool isFlowAlternately);
};
