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
    vector<float> avgAirTempOut;
    vector<float> avgWaterTempOut;

    //air
    float airVelocityInFrontHE;
    float airMaxVelocity;

    float airHydraulicDiam;

    float airFinsArea;
    float airTubeBetweenFinsArea;
    float airBareTubeArea;

    float airReynoldsNumb;
    float airPrandtlNumb;
    map<int, vector<float>> airBasicHTCAnalPerRow;
    map<int, vector<float>> airReducedHTCANalPerRow;
    map<int, vector<float>> airNusseltAnalPerRow;

    //Experiment
    vector <float> waterQsExp;
    vector <float> waterTempsInExp;
    vector <float> waterTempsOutExp;
    float airTempInExp;
    vector <float> airTempsOutExp;
    vector <float> airHeatPowersExp;

    //water
    float waterVelocity;

    float waterReynoldsNumb;
    float waterPrandtlNumb;
    map<int, vector<float>> waterHTC;

    //output
    float sumTotalAirHeatPower;
    vector<float> sumRowAirHeatPower;
    map<int, vector<float>> airAreaHeatPower;

    vector<float> avgAirHTCperRow;
    vector<float> avgAirNusseltNumbPerRow;

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
