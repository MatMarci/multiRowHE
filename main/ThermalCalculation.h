#pragma once

#include "ControlArea.h"


class ThermalCalculation
{

public:
    void airAndWaterOutTempCalc(map<int, vector<ControlArea>> &areas, bool isFlowAlternately, int iteration);
    void outTempCalc(ControlArea &area, int iteration, int row, int cArea);

    float airOutTempCalc(ControlArea area, int iteration);
    float waterOutTempCalc(ControlArea area, int iteration);

    float internalAvgAirTempCalc(ControlArea &area, int iteration);
    float avgWaterTempCalc(float waterInTemp, float waterOutTemp);

    float airParamNCalc(float airInTemp, float airOutTemp, float waterInTemp, float waterOutTemp);
    float waterParamNCalc(float airInTemp, float airOutTemp, float waterInTemp, float waterOutTemp);

    float UCoefCalc(float airInTemp, float airOutTemp, float waterInTemp, float waterOutTemp);
    float tubeAreaCalc();
    float airMassFlowCalc(float airInTemp, float airOutTemp);
    float reductAirHtcCalc(float airInTemp, float airOutTemp);

    float outBareTubeAreaCalc();
    float inBareTubeAreaCalc();
    float bareTubeBetweenFinsAreaCalc();
    float finAreaCalc();

    float waterHtcCalc(float waterInTemp, float waterOutTemp);
    float airHtcCalc(float airInTemp, float airOutTemp);
    float laminarWaterFlowNusseltNum(float waterReynoldNum, float waterPrandtlNum);
    float transientAndTurbulentWaterFlowNusseltNum(float waterReynoldNum, float waterPrandtlNum);
    float waterFricCoefCalc(float waterReynoldNum);


    float airReynoldsNumbCalc(float airInTemp, float airOutTemp);
    float airMaxVelocityCalc();
    float airPrandtlNumbCalc(float airInTemp, float airOutTemp);
    float airPrandtlNumbCalc(float airTemp);

    float waterReynoldsNumbCalc(float waterInTemp, float waterOutTemp);
    float waterPrandtlNumbCalc(float airInTemp, float airOutTemp);

    float airThermalConductCoefCalc(float airTemp);
    float airSpecHeatCalc(float airTemp);
    float airKinViscoCoefCalc(float airTemp);
    float airDensCalc(float airTemp);

    float waterSpecHeatCalc(float waterTemp);
    float waterThermalConductCoefCalc(float waterTemp);
    float waterKinViscoCoefCalc(float waterTemp);
    float waterDensCalc(float waterTemp);

    float airHydraulicDimCalc();

};
