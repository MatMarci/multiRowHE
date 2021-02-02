#pragma once

#include <ControlArea.h>
#include <Config.h>
#include <SimulationData.h>

class ResultsProcessing{

    SimulationData *simuData;
    Config *config;

public:
    ResultsProcessing(SimulationData *simuData, Config *config);

    void airNusseltPerRowCalc();
    float airUCoefBackwardCalc(int row);
    float alfaReductBackwardCalc(float airUCoefBackward);
    float alfa0BackwardCalc(float alfaReductBackward);
};
