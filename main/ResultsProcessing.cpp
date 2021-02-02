#include <ResultsProcessing.h>
#include <ThermalCalculation.h>

#include <math.h>

ResultsProcessing::ResultsProcessing(SimulationData *simuData, Config *config)
{
    this->simuData = simuData;
    this->config = config;
}

void ResultsProcessing::airNusseltPerRowCalc(){
    float airUCoefBackward;
    float alfaReductBackward;
    float alfa0Backward;

    for(auto row = 0; row < (int)(this->simuData->areas.size()); row++){
        airUCoefBackward = airUCoefBackwardCalc(row);
        alfaReductBackward = alfaReductBackwardCalc(airUCoefBackward);
        alfa0Backward = alfa0BackwardCalc(alfaReductBackward);
        //this->simuData->avgAirHTCperRow.push_back(alfa0Backward);
    }

    /*float airRowHtc;
    float sumAirTempOut;
    float avgAirTempOut;
    float sumAirTempIn;
    float avgAirTempIn;

    for(auto row = 0; row < (int)(this->simuData->areas.size()); row++){
        airRowHtc = 0;
        sumAirTempOut = 0;
        sumAirTempOut = 0;
        avgAirTempOut = 0;
        sumAirTempIn = 0;
        avgAirTempIn = 0;

        for(auto area = 0; area < (int)(this->simuData->areas[row].size()); area++){
            sumAirTempIn += this->simuData->areas[row][area].m_tempsAirIn.back();
            sumAirTempOut += this->simuData->areas[row][area].m_tempsAirOut.back();
        }

        float sumRowAirHeatPower = this->simuData->sumRowAirHeatPower[row];
        float airFinsArea = this->simuData->airFinsArea;
        float airTubeBetweenFinsArea = this->simuData->airTubeBetweenFinsArea;
        float airAreaRow = (this->simuData->airFinsArea + this->simuData->airTubeBetweenFinsArea) * this->config->CONTROL_AREAS;
        float airAreaBarRow = this->simuData->airBareTubeArea * this->config->CONTROL_AREAS;
        float CONTROL_AREAS = this->config->CONTROL_AREAS;

        avgAirTempIn = sumAirTempIn / config->CONTROL_AREAS;
        avgAirTempOut = sumAirTempOut / config->CONTROL_AREAS;
        airRowHtc = (this->simuData->sumRowAirHeatPower[row]/this->config->TUBES_IN_ROW)/(this->simuData->airBareTubeArea * this->config->CONTROL_AREAS * (avgAirTempOut - avgAirTempIn));
        this->simuData->avgAirHTCperRow.push_back(airRowHtc);
    }*/
}

float ResultsProcessing::airUCoefBackwardCalc(int row){
    float sumAirTempIn = 0;
    float sumAirTempOut = 0;
    float avgAirTempIn = 0;
    float avgAirTempOut = 0;

    for(auto area = 0; area < (int)(this->simuData->areas[row].size()); area++){
        sumAirTempIn += this->simuData->areas[row][area].m_tempsAirIn.back();
        sumAirTempOut += this->simuData->areas[row][area].m_tempsAirOut.back();
    }
    avgAirTempIn = sumAirTempIn / config->CONTROL_AREAS;
    avgAirTempOut = sumAirTempOut / config->CONTROL_AREAS;

    float airMassFlow = config->AIR_FLOW_PER_AREA * config->CONTROL_AREAS;
    float waterMassFlow = config->WATER_FLOW_PER_TUBE;
    float bareTubeArea = this->simuData->airBareTubeArea;
    float airTempIn = avgAirTempIn;
    float airTempOut = avgAirTempOut;
    float waterTempIn;
    float waterTempOut;

    ThermalCalculation tc(this->simuData, this->config);
    float avgAirSpecHeat = (tc.airSpecHeatCalc(airTempIn)+tc.airSpecHeatCalc(airTempOut))/2;


        waterTempIn = this->simuData->areas[row][0].m_tempsWaterIn.back();
        waterTempOut = this->simuData->areas[row][this->config->CONTROL_AREAS-1].m_tempsWaterOut.back();

    float avgWaterSpecHeat = (tc.waterSpecHeatCalc(waterTempIn)+tc.waterSpecHeatCalc(waterTempOut))/2;

    float airHeatPower = this->simuData->sumRowAirHeatPower[row]/this->config->TUBES_IN_ROW;

    float top;
    float bottom;
    float lnTop;
    float lnBottom;
    float ma_ca = airMassFlow*avgAirSpecHeat;
    float mw_cw = waterMassFlow*avgWaterSpecHeat;

    float etaError = 0.001;
    float resultCalc = 0;
    float Ucoef = 500;
    float step = 0.01;

    do{
        Ucoef += step;
        top = airHeatPower*((1/mw_cw)+(1/ma_ca));
        lnTop = waterTempIn - airTempIn;
        lnBottom = lnTop - top;
        bottom = log(lnTop/lnBottom);

        resultCalc = airHeatPower - (Ucoef*bareTubeArea*(top/bottom));
    }
    while(etaError < abs(resultCalc));
    this->simuData->avgAirHTCperRow.push_back(Ucoef);
}

float ResultsProcessing::alfaReductBackwardCalc(float airUCoefBackward){

}

float ResultsProcessing::alfa0BackwardCalc(float alfaReductBackward){

}

