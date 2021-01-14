#pragma once

#include <map>
#include <vector>

#include <ControlArea.h>

using namespace std;

class ControlArea;

class SimulationData{

    //inputData
    float airFlow;
    float waterFlowBeforeHE;
    float waterFlowInOnePipe;

    //resultsData
        //air
    float airVelocityInFrontHE;
    float airMaxVelocity;

    float airHydraulicDiam;

    float airFinsArea;
    float airTubeBetweenFinsArea;
    float airBareTubeArea;

    float airReynoldsNumb;
    float airPrandtlNumb;
    float airBasicHTC;
    float airReducedHTC;

        //water
    float waterVelocity;

    float waterReynoldsNumb;
    float waterPrandtlNumb;
    float waterHTC;

    //output
    float airHeatPower;
    float waterHeatPower;

    //tempsData
    map<int, vector<ControlArea>> areas;


    //methods


public:
    friend class ArrayOperation;
    friend class ThermalCalculation;
    friend class MainWindow;


};
