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
    void avgMediumsTempCalc();

    float airUCoefBackwardCalc(int row);
    float alfaReductBackwardCalc(int row, float airUCoefBackward);
    float alfa0BackwardCalc(int row, float alfaReductBackward);
    float airNusseltNumbCalc(int row, float alfa0Backward);
};
