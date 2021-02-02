#pragma once

#include <map>
#include <vector>

#include <ControlArea.h>

using namespace std;

class ControlArea;

class SimulationData{

    //HE params
    int pipesInRow;
    float totHeatTransferArea;

    //inputData
    float airFlow;
    float waterFlowBeforeHE;
    float waterFlowInOnePipe;

    //resultsData

    float colburnParam;
    float airNusseltNumb;

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
    float sumTotalAirHeatPower;
    vector<float> sumRowAirHeatPower;
    map<int, vector<float>> airAreaHeatPower;

    float avgAirHTC;
    vector<float> avgAirHTCperRow;
    map<int, vector<float>> airAreaHTC;

    float waterHeatPower;
    int iteration;

    //tempsData
    map<int, vector<ControlArea>> areas;


    //methods


public:
    friend class ArrayOperation;
    friend class ThermalCalculation;
    friend class MainWindow;
    friend class ResultsProcessing;
};
