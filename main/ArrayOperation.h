#pragma once

#include <SimulationData.h>
#include <map>
#include <vector>

using namespace std;

//class SimulationData;
class ControlArea;

class ArrayOperation
{
    SimulationData simuData;
    SimulationData *simuDataPointer;

public:
    SimulationData* initalizeModel(bool isFlowAlternately);
    void setAirAndWaterFlow(bool isFlowAlternately);
    void setInitialValues(bool isFlowAlternately);
    float avgErrorCalc(int iteration);
};
