#include <ResultsProcessing.h>
#include <ThermalCalculation.h>

#include <math.h>

ResultsProcessing::ResultsProcessing(SimulationData *simuData, Config *config)
{
    this->simuData = simuData;
    this->config = config;
}

void ResultsProcessing::airNusseltPerRowCalc(){
    ThermalCalculation tc(this->simuData, this->config);

    float airUCoefBackward;
    float alfaReductBackward;
    float alfa0Backward;


    for(auto row = 0; row < (int)(this->simuData->areas.size()); row++){
        float airNusseltuNumb = 0;
        //to separate
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

        float airMassFlow = tc.airMassFlowCalc(avgAirTempIn, avgAirTempOut) * config->CONTROL_AREAS;
        float avgAirSpecHeat = (tc.airSpecHeatCalc(avgAirTempOut)+tc.airSpecHeatCalc(avgAirTempIn))/2;

        //data from experiment
        int tubesInRow = this->config->TUBES_IN_ROW;
        float qWR1 = 896.19/tubesInRow;
        float qWR2 = qWR1 + (681.93/tubesInRow);
        float qWR3 = qWR2 + (545.31/tubesInRow);
        float qWR4 = qWR3 + (422.24/tubesInRow);
        this->simuData->waterQsExp = {qWR1, qWR2, qWR3, qWR4};
        this->simuData->airHeatPowersExp = {896.19, 681.93, 545.31, 422.24};
        this->simuData->waterTempsInExp = {40.17,40.17,40.17,40.17};
        this->simuData->waterTempsOutExp = {37.17, 37.89, 38.36, 38.76};

        this->simuData->airTempInExp = 23.34;
        float airTempInExp = this->simuData->airTempInExp;
        float airTempOutExpCalc = 0;
        (this->simuData->airTempsOutExp).push_back(airTempInExp);
        for(int i=1; i<this->config->ROWS+1; i++){
            airTempOutExpCalc = airTempInExp + (this->simuData->waterQsExp[i-1]/(airMassFlow*avgAirSpecHeat));
            (this->simuData->airTempsOutExp).push_back(airTempOutExpCalc);
        }

        /////////////////////
        airUCoefBackward = airUCoefBackwardCalc(row);
        alfaReductBackward = alfaReductBackwardCalc(row, airUCoefBackward);
        alfa0Backward = alfa0BackwardCalc(row, alfaReductBackward);
        airNusseltuNumb = airNusseltNumbCalc(row, alfa0Backward);
    }

}

void ResultsProcessing::avgMediumsTempCalc(){
    vector<float> airTempsOut;
    vector<float> waterTempsOut;
    float sumAirTempsOut;
    float sumWaterTempsOut;

    for(auto row = 0; row < (int)(this->config->ROWS); row++){
        sumAirTempsOut = 0;
        sumWaterTempsOut = 0;

        for(auto area = 0; area < (int)(this->simuData->areas[row].size()); area++){
            sumAirTempsOut += this->simuData->areas[row][area].tempsAirOut().back();
            sumWaterTempsOut += this->simuData->areas[row][area].tempsWaterOut().back();
        }
        this->simuData->avgAirTempOut.push_back(sumAirTempsOut/this->config->CONTROL_AREAS);
        this->simuData->avgWaterTempOut.push_back(sumWaterTempsOut/this->config->CONTROL_AREAS);
    }
}

float ResultsProcessing::airUCoefBackwardCalc(int row){
    //to separate
    ThermalCalculation tc(this->simuData, this->config);

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

    float airMassFlow = tc.airMassFlowCalc(avgAirTempIn, avgAirTempOut) * config->CONTROL_AREAS;
    float avgAirSpecHeat = (tc.airSpecHeatCalc(avgAirTempOut)+tc.airSpecHeatCalc(avgAirTempIn))/2;
    float ma_ca = airMassFlow*avgAirSpecHeat;

    //float waterMassFlow = config->WATER_FLOW_PER_TUBE;
    float bareTubeArea = this->simuData->airBareTubeArea* config->CONTROL_AREAS;
    //float fullFinnedArea = (this->simuData->airFinsArea+this->simuData->airTubeBetweenFinsArea)*this->config->CONTROL_AREAS;
    // float avgWaterSpecHeat = (tc.waterSpecHeatCalc(waterTempIn)+tc.waterSpecHeatCalc(waterTempOut))/2;
    //float airHeatPower = this->simuData->sumRowAirHeatPower[row]/this->config->TUBES_IN_ROW;
    //float mw_cw = waterMassFlow*avgWaterSpecHeat;

    float etaError = 0.001;
    float errorCalc;
    float airTempOutCalc = 0;
    float Ucoef =100;
    float step = 0.1;

    float Na = 0;
    //float Nw = (Ucoef*bareTubeArea)/(mw_cw);
    //float B;
    float avgWaterTempExp = ((this->simuData->waterTempsInExp[row] + this->simuData->waterTempsOutExp[row])/2);
    float airTempInExp = this->simuData->airTempsOutExp[row];
    float airTempOutExp = this->simuData->airTempsOutExp[row+1];

    do{
        Ucoef += step;
        Na = (Ucoef*bareTubeArea)/(ma_ca);
        //Nw = (Ucoef*bareTubeArea)/(mw_cw);
        //B = (Nw/Na)*(1-exp(-Na));
        airTempOutCalc = avgWaterTempExp - ((avgWaterTempExp-airTempInExp)*(exp(-Na)));
        errorCalc = abs(airTempOutCalc - airTempOutExp);
    }
    while(etaError < errorCalc);
    return Ucoef;
}

float ResultsProcessing::alfaReductBackwardCalc(int row, float airUCoefBackward){
    //float airInTemp = this->simuData->airTempsOutExp[row];
    //float airOutTemp = this->simuData->airTempsOutExp[row+1];
    float waterInTemp = this->simuData->waterTempsInExp[row];
    float waterOutTemp = this->simuData->waterTempsOutExp[row];

    ThermalCalculation tc(this->simuData, this->config);
    float outBareTubeArea = tc.outBareTubeAreaCalc();  //A_o
    float inBareTubeArea = tc.inBareTubeAreaCalc();  //A_in
    float avgTubeArea = (inBareTubeArea+outBareTubeArea)/2; //A_m
    float waterHtc = tc.waterHtcCalc(waterInTemp, waterOutTemp);

    float U = (1/airUCoefBackward);
    float A = (avgTubeArea/inBareTubeArea)*(this->config->TUBE_WALL_THICK/this->config->FIN_THERMAL_CONDUCT_COEF);
    float B = (outBareTubeArea/inBareTubeArea)*(1/waterHtc);
    float C = (U)-(A)-(B);

    float reductAirHtc = 1/(C);

    //this->simuData->avgAirHTCperRow.push_back(reductAirHtc);
    return reductAirHtc;
}

float ResultsProcessing::alfa0BackwardCalc(int row, float alfaReductBackward){
    ThermalCalculation tc(this->simuData, this->config);
    float bareTipeBetweenFinsArea = tc.bareTubeBetweenFinsAreaCalc();   // A_mf
    float finsArea = tc.finAreaCalc(); //A_f
    float outBareTubeArea = tc.outBareTubeAreaCalc();  //A_o

    float airHtc = (alfaReductBackward)/((bareTipeBetweenFinsArea/outBareTubeArea)+(this->config->FIN_EFF*finsArea/outBareTubeArea));
    this->simuData->avgAirHTCperRow.push_back(airHtc);
    return airHtc;
}

float ResultsProcessing::airNusseltNumbCalc(int row, float alfa0Backward){
    float sumAirTempIn = 0;
    float sumAirTempOut = 0;
    float airInTemp = 0;
    float airOutTemp = 0;

    for(auto area = 0; area < (int)(this->simuData->areas[row].size()); area++){
        sumAirTempIn += this->simuData->areas[row][area].m_tempsAirIn.back();
        sumAirTempOut += this->simuData->areas[row][area].m_tempsAirOut.back();
    }

    ThermalCalculation tc(this->simuData, this->config);
    airInTemp = sumAirTempIn / config->CONTROL_AREAS;
    airOutTemp = sumAirTempOut / config->CONTROL_AREAS;

    float avgAirThermalCondCoef = (tc.airThermalConductCoefCalc(airInTemp)+tc.airThermalConductCoefCalc(airOutTemp))/2;
    float hydDim = tc.airHydraulicDimCalc();

    float avgAirNusseltNumb = alfa0Backward * hydDim / avgAirThermalCondCoef;
    this->simuData->avgAirNusseltNumbPerRow.push_back(avgAirNusseltNumb);
    return avgAirNusseltNumb;
}

